//
// Created by naihai on 2020/2/19.
// Trainer class

#ifndef FMLEARN_SOLVER_TRAINER_H_
#define FMLEARN_SOLVER_TRAINER_H_

#include <string>
#include <vector>

#include "common/log.h"
#include "loss/loss.h"
#include "score/score.h"
#include "data/reader.h"

class Trainer {
 public:
  Trainer();
  ~Trainer();

  void Initialize();
  void Train();
  void CVTrain();

 private:

  void train(std::vector<DataReader*>& train_reader,
             std::vector<DataReader*>& test_reader);

  std::vector<DataReader *> reader_list_; // 既包括训练数据 也包括验证数据

  Loss* loss_;
  FMModel* model_;
};

#endif //FMLEARN_SOLVER_TRAINER_H_
