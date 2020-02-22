//
// Created by naihai on 2020/2/19.
// Predictor class

#ifndef FMLEARN_SOLVER_PREDICTOR_H_
#define FMLEARN_SOLVER_PREDICTOR_H_

#include <string>

#include "common/log.h"
#include "loss/loss.h"
#include "score/score.h"
#include "data/reader.h"

class Predictor {

 public:
  Predictor();
  ~Predictor();

  void Initialize(DataReader* reader,
                  Loss* loss,
                  FMModel* model,
                  std::string& out_file);
  void Predict();
  std::vector<float> GetResult() { return this->out_; };

 private:
  DataReader* reader_;

  Loss* loss_;
  FMModel* model_;
  std::vector<float> out_;
  std::string out_file_;
};

#endif //FMLEARN_SOLVER_PREDICTOR_H_
