//
// Created by naihai on 2020/1/12.
//

#ifndef FM__DATA_H_
#define FM__DATA_H_

#include <vector>
#include <iostream>

// 单个节点定义 一个样本
struct Node {
  Node(int feature_id, float feature_val) :
	  feature_id(feature_id), feature_val(feature_val) {}
  int feature_id; // 从0开始
  float feature_val;
};

typedef std::vector<Node> SparseRow;

// Data Matrix 稀疏矩阵
class DMatrix {
 public:
  DMatrix():row_length(0), rows(0), labels(0), has_label(false), norms(0){}
  ~DMatrix() = default;

  DMatrix(const DMatrix &other) = delete;
  void operator=(const DMatrix &other) = delete;

  void AddNode(int row_id, int feature_id, float feature_val);
  void AddRow();
  void Free(); // free memory for DMatrix
  int row_length = 0;
  bool has_label = false;

  std::vector<SparseRow *> rows; // 使用指针 防止内容拷贝
  std::vector<float> labels;
  std::vector<float> norms; // L2归一化
};

void DMatrix::AddNode(int row_id, int feature_id, float feature_val) {
  if (this->rows[row_id] == nullptr) {
	this->rows[row_id] = new SparseRow();
  }
  Node node(feature_id, feature_val);
  this->rows[row_id]->emplace_back(node);
}

void DMatrix::AddRow() {
  this->row_length++;
  this->rows.emplace_back(nullptr);
  this->norms.emplace_back(1.0);
  this->labels.emplace_back(0.0);
}

void DMatrix::Free() {
  // delete labels
  std::vector<float>().swap(this->labels);
  // delete norms
  std::vector<float>().swap(this->norms);

  // delete nodes
  for (int i = 0; i < this->row_length; ++i) {
	SparseRow *row = this->rows[i];
	if (nullptr != row) {
	  for (auto it = row->begin(); it != row->end(); ++it) {
		delete &it;
	  }
	}
  }

  // delete rows
  std::vector<SparseRow *>().swap(this->rows);
  this->row_length = 0;
}

#endif //FM__DATA_H_
