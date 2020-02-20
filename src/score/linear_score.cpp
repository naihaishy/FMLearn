//
// Created by naihai on 2020/1/28.
//

#include "score/linear_score.h"

float LinearScore::Calculate(SparseRow* row, FMModel& model, float norm) {
  float result = 0.0;

  float& w0 = model.GetBias();
  float*& W = model.GetW();

  result += w0;
  // linear term
  for (auto& it : *row) {
    int i = it.feature_id;
    float xi = it.feature_val;
    result += W[i] * xi * norm;
  }
  return result;
}
void LinearScore::CalGrad(SparseRow* row, FMModel& model, float norm, float delta) {

}


