//
// Created by naihai on 2020/1/23.
//

#include "squared_loss.h"
#include <cassert>

/**
 * 计算loss
 * @param preds
 * @param labels
 * @return
 */
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
 * 计算梯度
 * @param data
 * @param model
 * @return
 */
float SquaredLoss::CalGrad(DMatrix* data, FMModel* model) {
  return Loss::CalGrad(data, model);
}
