//
// Created by naihai on 2020/1/23.
//

#ifndef FMLEARN_LOSS_SQUARED_LOSS_H_
#define FMLEARN_LOSS_SQUARED_LOSS_H_
#include "loss.h"
class SquaredLoss : public Loss {
 public:
  float Calculate(std::vector<float>& preds,
                  std::vector<float>& labels) override;

  float CalGrad(DMatrix* data, FMModel* model) override;

};

#endif //FMLEARN_LOSS_SQUARED_LOSS_H_
