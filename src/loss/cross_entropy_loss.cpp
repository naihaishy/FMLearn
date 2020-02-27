//
// Created by naihai on 2020/1/23.
//

#include "loss/cross_entropy_loss.h"

#include <cassert>
#include <common/log.h>

inline float sigmoid(float x) {
  return 1.0f / (1.0f + expf(-x));
}

/**
 * 累计计算 Loss
 * @param preds
 * @param labels
 * @return
 */
void CrossEntropyLoss::Calculate(std::vector<float>& preds,
                                 std::vector<float>& labels) {
  float result = 0.0f;
  assert(preds.size() == labels.size());
  for (int i = 0; i < preds.size(); ++i) {
    result += log1p(exp(preds[i] * labels[i])); // -ln sigmoid(yy^)
  }
  loss_sum_ += result;
  num_samples_ += preds.size();
}

/**
 * 计算梯度并更新参数
 * @param data
 * @param model
 * @param score
 * @return
 */
void CrossEntropyLoss::CalGrad(const DMatrix* data, FMModel* model) {
  // check
  assert(model->GetTask() == CLASSIFICATION);

  float losses = 0.0;

  for (int m = 0; m < data->row_length; ++m) {
    auto& x = data->rows[m];
    auto norm = data->norms[m];

    // predict instance
    float y_pred = score_->Calculate(x, *model, norm);
    float y_true = data->labels[m];

    // calculate gradient and update weights
    float delta = (sigmoid(y_true * y_pred) - 1) * y_true;
    // LogInfo(score_->GetType());
    score_->CalGrad(x, *model, norm, delta);

    // calculate loss
    losses += static_cast<float> (-log(sigmoid(y_true * y_pred)));
  }

  loss_sum_ += losses;
  num_samples_ += data->row_length;
}

