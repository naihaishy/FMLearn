//
// Created by naihai on 2020/2/19.
//

#include <score/score.h>
#include <score/fm_score.h>
#include <loss/cross_entropy_loss.h>
#include "gtest/gtest.h"
#include "solver/trainer.h"

TEST(SOLVER_TEST, Trainer) {
  HyperParam* hyper_param = new HyperParam;
  hyper_param->is_train = true;
  Score* score = new FmScore();
  score->Initialize(hyper_param);

  Loss* loss = new CrossEntropyLoss();
  loss->Initialize(score);

  FMModel* model = new FMModel(1, 12, 12, 0, 0);

  Trainer trainer;
  std::vector<DataReader*> reader_list;
  reader_list.emplace_back(new DataReader("", false));
  trainer.Initialize(reader_list,
                     loss,
                     model,
                     nullptr,
                     12,
                     true,
                     3,
                     false);
}
