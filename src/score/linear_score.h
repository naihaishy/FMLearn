//
// Created by naihai on 2020/1/28.
// 线性回归函数

#ifndef FMLEARN_SCORE_LINEAR_SCORE_H_
#define FMLEARN_SCORE_LINEAR_SCORE_H_

#include "score/score.h"

class LinearScore : public Score {
 public:
  float Calculate(const SparseRow* row, FMModel& model, float norm) override;
  void CalGrad(const SparseRow* row, FMModel& model, float norm, float delta) override;
  std::string GetType() override { return type_; }

 private:
  std::string type_ = "LinearScore";
};

#endif //FMLEARN_SCORE_LINEAR_SCORE_H_

