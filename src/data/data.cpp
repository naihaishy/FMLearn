//
// Created by naihai on 2020/1/13.
//
#include "data.h"

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

