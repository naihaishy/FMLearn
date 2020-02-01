//
// Created by naihai on 2020/1/23.
//

#include "loss/cross_entropy_loss.h"

#include <cassert>

inline float sigmoid(float x) {
  return 1.0f / (1.0f + expf(-x));
}

/**
 * 计算 Loss
 * @param preds
 * @param labels
 * @return
 */
float CrossEntropyLoss::Calculate(std::vector<float>& preds,
                                  std::vector<float>& labels) {
  float result = 0.0f;
  assert(preds.size() == labels.size());
  for (int i = 0; i < preds.size(); ++i) {
    result += log1p(exp(preds[i] * labels[i]));
  }
  return result;
}

/**
 *
 * @param data
 * @param model
 * @param score
 * @return
 */
float CrossEntropyLoss::CalGrad(DMatrix* data, FMModel* model, FMHyperParam* hyper_param, Score* score) {
  // check
  assert(model->task_ == CLASSIFICATION);

  float losses = 0.0;

  for (int m = 0; m < data->row_length; ++m) {
    auto& x = data->rows[m];
    auto norm = data->norms[m];

    // predict instance
    float y_pred = score->Calculate(x, model, norm);
    float y_true = data->labels[m];

    // calculate gradient and update weights
    float delta = (sigmoid(y_true * y_pred) - 1) * y_true;
    score->CalGrad(x, model, hyper_param, norm, delta);

    // calculate loss
    losses += -log(sigmoid(y_true * y_pred));
  }
  return losses / data->row_length;
}
CrossEntropyLoss::~CrossEntropyLoss() = default;
