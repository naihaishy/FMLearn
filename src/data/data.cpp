//
// Created by naihai on 2020/1/13.
//

#include "data/data.h"

#include <iostream>
#include <cassert>
#include <algorithm>

#include "data/reader.h"

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
 * 从文件中构造DMatrix 稠密数据
 * @param file_name 文件名
 * @param has_label 是否存在label
 */
DMatrix::DMatrix(const std::string& file_name, bool has_label) {
  DataReader* reader = new DataReader(file_name, has_label);
  reader->Initialize();
  reader->Read(this);
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

/**
 * 特征数目
 * @return
 */
int DMatrix::GetNumFeatures() {
  if (row_length <= 0) return 0;
  int num_features = 0;
  for (const Node& node: *(rows[0])) {
    num_features = std::max(num_features, node.feature_id);
  }
  return num_features;
}




