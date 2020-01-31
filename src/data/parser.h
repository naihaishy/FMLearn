//
// Created by naihai on 2020/1/31.
// 从一行数据中 解析出格式化数据 针对行的操作

#ifndef FMLEARN_DATA_PARSER_H_
#define FMLEARN_DATA_PARSER_H_

#include "data.h"
#include "src/common/log.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <src/common/utils.h>

class Parser {
 public:
  void Initialize(char delimiter, bool has_header, bool has_label) {
    delimiter_ = delimiter;
    has_header_ = has_header;
    has_label_ = has_label;
  }
  virtual void Parse(DMatrix* data, const std::string& line) = 0;
 protected:
  char delimiter_ = ','; // 数据项分隔符 \t , space
  bool has_header_ = false;
  bool has_label_ = false; // 如果有label,一定要放在头部 即第一列
};

/**
 * CSVParser
 * [y1 feat_1 feat_2 feat_3 ... feat_n]
 */
class CSVParser : public Parser {
 public:
  void Parse(DMatrix* data, const std::string& line) override {
    data->AddRow();
    int i = data->row_length - 1; // 标记该行记录所处的行号
    float norm = 0.0;

    std::vector<float> line_arr = split_in_float(line, delimiter_);

    int n_cols = line_arr.size();
    int feature_start = 0;
    if (has_label_) {
      float label = line_arr[0];// 第一列是 label
      data->labels[i] = label;
      data->min_label = std::min(data->min_label, label);
      data->max_label = std::max(data->max_label, label);
      feature_start = 1;
    }

    for (int j = feature_start; j < n_cols; ++j) {
      float value = line_arr[j];
      data->AddNode(i, j, value);
      norm += value * value;
    }
    norm = 1.0f / norm;
    data->norms[i] = norm;
  }
};

/**
 * LibSVMParser
 * [y1 idx:value idx:value ...]
 */
class LibSVMParser : public Parser {
 public:
  void Parse(DMatrix* data, const std::string& line) override {
    data->AddRow();
    int i = data->row_length - 1; // 标记该行记录所处的行号
    float norm = 0.0;

    std::vector<std::string> line_arr = split_in_string(line, delimiter_);

    int n_cols = line_arr.size();
    int feature_start = 0;
    if (has_label_) {
      float label = std::stof(line_arr[0]);// 第一列是 label
      data->labels[i] = label;
      data->min_label = std::min(data->min_label, label);
      data->max_label = std::max(data->max_label, label);
      feature_start = 1;
    }

    for (int j = feature_start; j < n_cols; ++j) {
      std::string item = line_arr[j]; // 1:12
      auto found = item.find(':');
      int idx = std::stoi(item.substr(0, found));
      float value = std::stof(item.substr(found + 1));
      data->AddNode(i, idx, value);
      norm += value * value;
    }
    norm = 1.0f / norm;
    data->norms[i] = norm;
  }
};

/**
 * LibFFMParser
 * [y1 field:idx:value field:idx:value ...]
 */
class LibFFMParser : public Parser {
 public:
  void Parse(DMatrix* data, const std::string& line) override {
    data->AddRow();
    int i = data->row_length - 1; // 标记该行记录所处的行号
    float norm = 0.0;

    std::vector<std::string> line_arr = split_in_string(line, delimiter_);

    int n_cols = line_arr.size();
    int feature_start = 0;
    if (has_label_) {
      float label = std::stof(line_arr[0]);// 第一列是 label
      data->labels[i] = label;
      data->min_label = std::min(data->min_label, label);
      data->max_label = std::max(data->max_label, label);
      feature_start = 1;
    }

    for (int j = feature_start; j < n_cols; ++j) {
      std::string item = line_arr[j]; // 1:3:12
      auto found_1 = item.find_first_of(':');
      auto found_2 = item.find_last_of(':');
      int field_id = std::stoi(item.substr(0, found_1));
      int feature_id = std::stoi(item.substr(found_1 + 1, found_2));
      float value = std::stof(item.substr(found_2 + 1));
      data->AddNode(i, feature_id, value);
      norm += value * value;
    }
    norm = 1.0f / norm;
    data->norms[i] = norm;
  }
};

#endif //FMLEARN_DATA_PARSER_H_
