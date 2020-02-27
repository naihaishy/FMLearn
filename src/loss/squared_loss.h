//
// Created by naihai on 2020/1/23.
//

#ifndef FMLEARN_LOSS_SQUARED_LOSS_H_
#define FMLEARN_LOSS_SQUARED_LOSS_H_

#include "loss/loss.h"

class SquaredLoss : public Loss {
 public:
  void Calculate(std::vector<float>& preds,
                  std::vector<float>& labels) override;

  void CalGrad(const DMatrix* data, FMModel* model) override;
  std::string GetType() override { return type_; }

 private:
  std::string type_ = "SquaredLoss" ;
};

#endif //FMLEARN_LOSS_SQUARED_LOSS_H_
