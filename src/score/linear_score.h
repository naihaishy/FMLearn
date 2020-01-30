//
// Created by naihai on 2020/1/28.
// 线性回归函数

#ifndef FMLEARN_SCORE_LINEAR_SCORE_H_
#define FMLEARN_SCORE_LINEAR_SCORE_H_

#include "score.h"

class LinearScore : public Score {
 public:
  ~LinearScore() override = default;
  float Calculate(SparseRow* row, FMModel* model, float norm) override;
  void CalGrad(SparseRow* row, FMModel* model, FMHyperParam* hyper_param, float norm, float delta) override;

 private:
  std::string type_ = "LinearScore";
};

#endif //FMLEARN_SCORE_LINEAR_SCORE_H_

