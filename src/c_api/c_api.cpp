//
// Created by naihai on 2020/1/12.
//
#include "c_api.h"
#include "../data/data.h"
#include "c_api_error.h"
#include <iostream>
#include <memory>

FM_DLL void hello() {
  std::cout << "Hello, World!" << std::endl;
}

FM_DLL int FMCreate(FM* out) {
  std::cout << "FMCreate " << std::endl;
  return 0;
}

FM_DLL int FMFit(FM* model, DataHandle* X, DataHandle* y, int iterations) {
  std::cout << "FMFit " << std::endl;
  return 0;
}

FM_DLL int FMPredict(FM* model, DataHandle* X) {
  std::cout << "FMPredict " << std::endl;
  return 0;
}

// 创建DMatrix
/**
 * 创建DMatrix
 * @param data pointer to the data space
 * @param rows number of data samples
 * @param cols number of data features
 * @param label pointer to the label space
 * @param out the created data matrix
 */
FM_DLL int FMMatrixCreateFromMat(const float* data, int rows, int cols, const float* label, DataHandle* out) {
  API_BEGIN();
  // 使用智能指针管理DMatrix
  std::unique_ptr<DMatrix> matrix(new DMatrix());

  for (int i = 0; i < rows; ++i) {
	matrix->AddRow();
	float norm = 0.0;
	for (int j = 0; j < cols; ++j) {
	  float value = data[i * cols + j];
	  matrix->AddNode(i, j, value);
	  norm += value * value;
	}
	norm = 1.0f / norm;
	matrix->norms[i] = norm;
  }

  if (nullptr == label) {
	matrix->has_label = false;
  } else {
	matrix->has_label = true;
	for (int i = 0; i < rows; ++i) {
	  matrix->labels[i] = label[i];
	}
  }

  *out = matrix.release();
  std::cout << "data matrix created succeed " << std::endl;
  API_END();
}

FM_DLL int FMMatrixFree(DataHandle* out) {
  API_BEGIN();
  // 强制类型转换为DMatrix
  DMatrix *matrix = reinterpret_cast<DMatrix *>(out);
  matrix->Free();
  delete matrix;
  API_END();
}
