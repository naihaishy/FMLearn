//
// Created by naihai on 2020/2/20.
// Entry Class

#ifndef FMLEARN_SOLVER_SOLVER_H_
#define FMLEARN_SOLVER_SOLVER_H_

#include "score/score.h"
#include "loss/loss.h"
#include "metric/metric.h"
#include "core/fm_model.h"
#include "core/fm_param.h"
#include "common/thread_pool.h"
#include "data/reader.h"
#include "cli/cli_param.h"

/**
 * Usage :
 *  Solver solver;
 *  solver.SetTrain(); // solver.SetPredict();
 *  solver.Initialize();
 *  solver.Start();
 */

class Solver {

 public:
  void Initialize(int argc, char* argv[]);
  void SetTrain();
  void SetPredict();
  void Start();

 private:
  void InitTrain();
  void InitPredict();
  void StartTrain();
  void StartPredict();

  std::vector<DataReader*> reader_list_;
  Score* score_;
  FMModel* model_;
  Loss* loss_;
  Metric *metric_;
  FMHyperParam* hyper_param_;
  ThreadPool* pool_;
};

#endif //FMLEARN_SOLVER_SOLVER_H_
