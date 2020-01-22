//
// Created by naihai on 2020/1/13.
//

#include <src/common/common.h>
#include "data.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cassert>
#include <src/common/log.h>
#include <src/common/utils.h>

/**
 * 使用C数组直接构造DMatrix
 * @param data 一维数组指针 基于行存储格式二维数据 稠密数据
 * @param label 一维数组指针
 * @param n_rows 行数 样本数目
 * @param n_cols 列数 特征数目
 */
DMatrix::DMatrix(const float* data, const float* label, int n_rows, int n_cols) {
  // 预分配内存
  this->Init(n_rows);

  for (int i = 0; i < n_rows; ++i) {
    this->AddRow();
    float norm = 0.0;
    for (int j = 0; j < n_cols; ++j) {
      float value = data[i * n_cols + j];
      this->AddNode(i, j, value);
      norm += value * value;
    }
    norm = 1.0f / norm;
    this->norms[i] = norm;
  }

  if (nullptr == label) {
    this->has_label = false;
  } else {
    this->has_label = true;
    for (int i = 0; i < n_rows; ++i) {
      this->labels[i] = label[i];
      min_label = this->labels[i] < min_label ? this->labels[i] : min_label;
      max_label = this->labels[i] > max_label ? this->labels[i] : max_label;
    }
  }
}

/**
 * 使用C++ Vector直接构造DMatrix
 * @param data 二维Vector指针 稠密数据
 * @param label 一维Vector指针 标签
 */
DMatrix::DMatrix(std::vector<std::vector<float>>* data, std::vector<float>* label) {
  assert(data->size() == label->size());
  int n_rows = data->size();
  int n_cols = (*data)[0].size();
  // 预分配内存
  this->Init(n_rows);

  for (int i = 0; i < n_rows; ++i) {
    this->AddRow();
    float norm = 0.0;
    for (int j = 0; j < n_cols; ++j) {
      float value = (*data)[i][j];
      this->AddNode(i, j, value);
      norm += value * value;
    }
    norm = 1.0f / norm;
    this->norms[i] = norm;
  }

  if (nullptr == label) {
    this->has_label = false;
  } else {
    this->has_label = true;
    for (int i = 0; i < n_rows; ++i) {
      this->labels[i] = (*label)[i];
      min_label = this->labels[i] < min_label ? this->labels[i] : min_label;
      max_label = this->labels[i] > max_label ? this->labels[i] : max_label;
    }
  }
}

/**
 * 从文件中构造DMatrix
 * @param file_name 文件名
 * @param file_format 文件格式，目前支持csv txt TODO 支持libsvm, libffm
 * @param seq 列分割符
 */
DMatrix::DMatrix(const std::string& file_name) {
  DMatrix(file_name, "csv", ",", true);
}

DMatrix::DMatrix(const std::string& file_name,
                 const std::string& file_format,
                 const std::string& sep,
                 bool has_label) {
  std::ifstream infile(file_name, std::ios::in);
  if (file_format != "csv" && file_format != "txt") {
    Logging::error("file format " + file_format + " is not supported yet");
    throw std::runtime_error("file_format is not valid");
  }
  if (!infile.good()) {
    Logging::error("file " + file_name + " not exists");
    throw std::runtime_error("file_name is not valid");
  }

  if (infile.is_open()) {
    std::string line;
    // std::vector<float> row;
    int n_cols = 0;
    int i = 0;
    this->has_label = has_label;

    while (infile.good()) {
      getline(infile, line);
      if (line.empty()) break;
      // 解析行数据
      // std::cout << line << std::endl;
      auto row = split_in_float(line, sep[0]);
      n_cols = row.size();
      assert(n_cols > 0);
      this->AddRow();
      float norm = 0.0;

      int feature_start = 0;
      if (has_label) {
        this->labels[i] = row[0]; // 第一列是 label
        min_label = this->labels[i] < min_label ? this->labels[i] : min_label;
        max_label = this->labels[i] > max_label ? this->labels[i] : max_label;
        feature_start = 1;
      }

      for (int j = feature_start; j < n_cols; ++j) {
        float value = row[j];
        this->AddNode(i, j, value);
        norm += value * value;
      }
      norm = 1.0f / norm;
      this->norms[i] = norm;
      i++;
    }
    Logging::debug("DMatrix construct done");

  } else {
    Logging::error("file is closed before read data");
    throw std::runtime_error("input file is closed");
  }
}

/**
 * 预分配内存 提高性能 可以不调用该函数
 * @param n_rows 记录数目
 */
void DMatrix::Init(int n_rows) {
  this->labels.reserve(n_rows);
  this->norms.reserve(n_rows);
  this->rows.reserve(n_rows);
}

/**
 * DMatrix为某一行记录添加一个特征记录
 * @param row_id
 * @param feature_id
 * @param feature_val
 */
void DMatrix::AddNode(int row_id, int feature_id, float feature_val) {
  if (this->rows[row_id] == nullptr) {
    this->rows[row_id] = new SparseRow();
  }
  Node node(feature_id, feature_val);
  this->rows[row_id]->emplace_back(node);
}

/**
 * DMatrix添加一行记录
 */
void DMatrix::AddRow() {
  this->row_length++;
  this->rows.emplace_back(nullptr);
  this->norms.emplace_back(1.0);
  this->labels.emplace_back(0.0);
}

/**
 * 释放DMatrix内存
 */
void DMatrix::Free() {
  this->has_label = true;
  // delete labels
  std::vector<float>().swap(this->labels);
  // delete norms
  std::vector<float>().swap(this->norms);

  // delete nodes
  for (int i = 0; i < this->row_length; ++i) {
    SparseRow* row = this->rows[i];
    delete row;
  }

  // delete rows
  std::vector<SparseRow*>().swap(this->rows);
  this->row_length = 0;
}

/**
 * 比较两个DMatrix内容是否相等
 * @param other DMatrix
 * @return bool
 */
bool DMatrix::operator==(const DMatrix& other) const {
  if (this == &other) return true;
  if (this->has_label != other.has_label) return false;
  if (this->row_length != other.row_length) return false;
  // if (this->rows!= other.rows) return false; // 不能直接判断SparseRow* 相等
  if (this->labels != other.labels) return false;
  if (this->norms != other.norms) return false;

  for (int i = 0; i < this->row_length; ++i) {
    if ((*this->rows[i]) != (*other.rows[i])) return false;
  }
  return true;
}

bool DMatrix::operator!=(const DMatrix& other) const {
  return !(*this == other);
}




