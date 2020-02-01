//
// Created by naihai on 2020/1/23.
//

#include <cassert>

#include "loss/squared_loss.h"

float SquaredLoss::Calculate(std::vector<float>& preds,
                             std::vector<float>& labels) {
  float result = 0.0f;
  assert(preds.size() == labels.size());
  for (int i = 0; i < preds.size(); ++i) {
    result += (labels[i] - preds[i]) * (labels[i] - preds[i]);
  }
  return result / 2;
}

/**
 * 计算梯度并更新参数
 * @param data
 * @param model
 * @param score
 * @return
 */
float SquaredLoss::CalGrad(DMatrix* data, FMModel* model, FMHyperParam* hyper_param, Score* score) {
  // check
  assert(model->GetTask() == REGRESSION);

  float losses = 0.0;

  for (int m = 0; m < data->row_length; ++m) {
    auto& x = data->rows[m];
    auto norm = data->norms[m];

    // predict instance
    float y_pred = score->Calculate(x, model, norm);
    float y_true = data->labels[m];

    // calculate gradient and update weights
    float delta = y_pred - y_true;
    score->CalGrad(x, model, hyper_param, norm, delta);

    // calculate loss
    losses += 0.5f * (y_pred - y_true) * (y_pred - y_true);
  }
  return losses / data->row_length;
}
SquaredLoss::~SquaredLoss() = default;
