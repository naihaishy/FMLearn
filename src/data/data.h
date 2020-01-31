//
// Created by naihai on 2020/1/12.
//
#ifndef FMLEARN_DATA_H_
#define FMLEARN_DATA_H_

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <limits>

// 单个节点定义 一个样本
struct Node {
  Node(int feature_id, float feature_val) :
      feature_id(feature_id), feature_val(feature_val) {};
  int feature_id; // 从0开始
  float feature_val;
  // 重载输出运算符
  friend std::ostream& operator<<(std::ostream& out, Node& node) {
    out << "feature_id: " << node.feature_id << "\t" << "feature_val: " << node.feature_val;
    return out;
  };

  bool operator==(const Node& other) const {
    return (this->feature_id == other.feature_id) &&
        (fabsf(this->feature_val - other.feature_val) < 1e-6);
  }
};

typedef std::vector<Node> SparseRow;

// Data Matrix 稀疏矩阵
class DMatrix {
 public:
  DMatrix() : row_length(0), has_label(true), rows(0), labels(0), norms(0) {}
  ~DMatrix() = default;

  explicit DMatrix(const float* data, const float* label, int n_rows, int n_cols);
  explicit DMatrix(std::vector<std::vector<float>>* data, std::vector<float>* labels);
  explicit DMatrix(const std::string& file_name, bool has_label = true);

  DMatrix(const DMatrix& other) = delete;
  void operator=(const DMatrix& other) = delete;
  bool operator==(const DMatrix& other) const;
  bool operator!=(const DMatrix& other) const;

  void Init(int n_rows); // pre alloc memory for rows, labels, norms
  void AddNode(int row_id, int feature_id, float feature_val);
  void AddRow();
  void Free(); // Free memory for DMatrix
  int GetNumFeatures() { return n_features; }
  int row_length = 0;
  bool has_label = true;
  int n_features = 0;

  std::vector<SparseRow*> rows; // 使用指针 防止内容拷贝
  std::vector<float> labels;
  std::vector<float> norms; // L2归一化

  // label的最大最小值
  float min_label = std::numeric_limits<float>::max();
  float max_label = std::numeric_limits<float>::min();
};

#endif //FMLEARN_DATA_H_
