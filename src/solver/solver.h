//
// Created by naihai on 2020/2/20.
// Entry Class

#ifndef FMLEARN_SOLVER_SOLVER_H_
#define FMLEARN_SOLVER_SOLVER_H_

#include "score/score.h"
#include "loss/loss.h"
#include "metric/metric.h"
#include "model/fm_model.h"
#include "model/hyper_param.h"
#include "common/thread_pool.h"
#include "data/reader.h"

/**
 * Usage :
 *  Solver solver;
 *  solver.SetTrain(); // solver.SetPredict();
 *  solver.Initialize();
 *  solver.Start();
 */

class Solver {

 public:
  Solver() :
      score_(nullptr),
      loss_(nullptr),
      model_(nullptr),
      metric_(nullptr) {};
  ~Solver() = default;;
  void Initialize(HyperParam* param);
  void SetTrain();
  void SetPredict();
  void Start();

 private:
  void InitTrain();
  void InitPredict();
  void StartTrain();
  void StartPredict();

  // 存储训练数据和验证数据 或者存在测试数据
  std::vector<DataReader*> reader_list_;
  Score* score_;
  Loss* loss_;
  FMModel* model_;
  Metric* metric_;
  HyperParam* hyper_param_;
  ThreadPool* pool_;
};

#endif //FMLEARN_SOLVER_SOLVER_H_
