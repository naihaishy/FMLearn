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
 *  solver.Initialize(param);
 *  solver.Start();
 */

class Solver {

 public:
  Solver() :
      loss_(nullptr),
      model_(nullptr),
      metric_(nullptr),
      param_(nullptr),
      pool_(nullptr) {};
  ~Solver();

  void Initialize(HyperParam* param);

  void Start();

 private:
  void InitTrain();
  void InitPredict();
  void StartTrain();
  void StartPredict();

  // 存储训练数据和验证数据 或者存在测试数据
  std::vector<DataReader*> reader_list_;
  Loss* loss_;
  FMModel* model_;
  Metric* metric_;
  HyperParam* param_;
  ThreadPool* pool_;
};

#endif //FMLEARN_SOLVER_SOLVER_H_
