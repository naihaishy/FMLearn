//
// Created by naihai on 2020/1/23.
// 计算损失函数 损失函数对参数梯度值

#ifndef FMLEARN_LOSS_LOSS_H_
#define FMLEARN_LOSS_LOSS_H_

#include "src/data/data.h"
#include "src/core/fm_model.h"

#include <vector>

class Loss {

 public:
  Loss() = default;

  virtual float Calculate(std::vector<float>& preds,
                          std::vector<float>& labels) = 0;
  virtual float CalGrad(DMatrix* data, FMModel* model) = 0;
  ~Loss();

 private:
  double loss_sum = 0.0;
  int data_samples = 0;

};

#endif //FMLEARN_LOSS_LOSS_H_
