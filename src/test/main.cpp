//
// Created by naihai on 2020/1/13.
//
#include <memory>
#include "../core/model.h"
using namespace std;
typedef void * DataHandle;

void FMMatrixCreateFromMat(const float* data, int rows, int cols, const float* label) {
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

  std::cout << "data matrix created succeed" << std::endl;
}

int main() {

  auto model = new FactorizationMachine(0, 10, 10,
										0.1, 0.1, 0.1, 0.1,
										0.0, 0.1);

  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
							1.0, 2.0, 3.0, 4.0, 5.0,
							1.0, 2.0, 3.0, 4.0, 5.0,
							1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};
  FMMatrixCreateFromMat(data, 3, 5, label);
  // DMatrix *matrix = reinterpret_cast<DMatrix *>(*out);

  // model->Fit()
}

