//
// Created by naihai on 2020/2/19.
// Predictor class

#ifndef FMLEARN_SOLVER_PREDICTOR_H_
#define FMLEARN_SOLVER_PREDICTOR_H_

#include "common/log.h"
#include "loss/loss.h"
#include "score/score.h"
#include "data/reader.h"

class Predictor {

 public:
  Predictor();
  ~Predictor();

  void Predict();
  std::vector<float> GetResult() { return this->out_; };

 private:
  DataReader* reader_;
  std::vector<float> out_;
  FMModel *model_;
};

#endif //FMLEARN_SOLVER_PREDICTOR_H_
