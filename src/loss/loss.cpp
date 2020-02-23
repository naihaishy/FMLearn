//
// Created by naihai on 2020/1/23.
//

#include "loss/loss.h"

void Loss::Predict(const DMatrix* data, FMModel& model, std::vector<float>& preds){
  preds.clear();
  preds.reserve(data->row_length);
  for (int m = 0; m < data->row_length; ++m) {
    auto& x = data->rows[m];
    float norm = data->norms[m];
    // predict
    float y_pred = score_->Calculate(x, model, norm);
    preds.emplace_back(y_pred);
  }
}