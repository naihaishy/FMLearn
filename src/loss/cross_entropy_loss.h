//
// Created by naihai on 2020/1/23.
//

#ifndef FMLEARN_LOSS_CROSS_ENTROPY_LOSS_H_
#define FMLEARN_LOSS_CROSS_ENTROPY_LOSS_H_

#include "core/hyper_param.h"
#include "core/fm_model.h"
#include "data/data.h"
#include "score/score.h"

#include "loss/loss.h"

class CrossEntropyLoss : public Loss {
 public:
  ~CrossEntropyLoss() override;
  void Calculate(std::vector<float>& preds,
                  std::vector<float>& labels) override;
  float CalGrad(DMatrix* data, FMModel* model) override;
  std::string GetType() override { return type_; }

 private:
  std::string type_ = "CrossEntropyLoss";
};

#endif //FMLEARN_LOSS_CROSS_ENTROPY_LOSS_H_
