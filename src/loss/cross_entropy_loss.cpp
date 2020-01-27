//
// Created by naihai on 2020/1/23.
//

#include "cross_entropy_loss.h"
#include <cassert>

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
 * 计算梯度
 * @param data
 * @param model
 * @return
 */
float CrossEntropyLoss::CalGrad(DMatrix* data, FMModel* model) {
  return Loss::CalGrad(data, model);
}
