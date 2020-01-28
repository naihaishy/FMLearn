//
// Created by naihai on 2020/1/28.
//

#include "linear_score.h"

float LinearScore::Calculate(SparseRow* row, FMModel* model, float norm) {
  float result = 0.0;
  result += model->w0_;
  // linear term
  for (auto& it : *row) {
    int i = it.feature_id;
    float xi = it.feature_val;
    result += model->W_[i] * xi * norm;
  }
  return result;
}
void LinearScore::CalGrad(SparseRow* row, FMModel* model, FMHyperParam* hyper_param, float norm, float delta) {


}


