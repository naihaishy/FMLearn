//
// Created by naihai on 2020/1/13.
//

#ifndef FMLEARN_CORE_MODEL_H_
#define FMLEARN_CORE_MODEL_H_

#include "common/common.h"
#include "common/thread_pool.h"
#include "data/data.h"
#include "loss/loss.h"
#include "score/score.h"

#include "core/fm_model.h"
#include "core/hyper_param.h"

// Entry class for FM FM的入口类
class FactorizationMachine {
 public:
  // Constructor and Destructor
  FactorizationMachine(int task, int n_features, int n_factors,
                       float lr, float reg_w0, float reg_W, float reg_V,
                       float mean, float stddev,
                       bool norm, bool verbose);

  //  从模型文件中构建FactorizationMachine
  explicit FactorizationMachine(const std::string& model_file);

  ~FactorizationMachine();
  FactorizationMachine(const FactorizationMachine& other) = delete;
  void operator=(const FactorizationMachine&) = delete;

  void Initialize();

  void Fit(DMatrix* data, int epochs, bool multi_thread = false, int n_threads = 1);

  std::vector<float> Predict(DMatrix* data);

  HyperParam* GetHyperParam() const { return this->hyper_param_; }
  FMModel* GetModel() const { return this->model_; }
  Score* GetScore() const { return score_; }
  Loss* GetLoss() const { return loss_; }

  friend void FMFitInSingleThread(const DMatrix* data, FactorizationMachine* fm,
                                   int start, int end, float *loss);

 private:
  void FitInMultiThread(DMatrix* data, int epochs, int num_threads);
  void FitInSingleThread(DMatrix* data, int epochs);

  HyperParam* hyper_param_;
  FMModel* model_;
  Loss* loss_;
  Score* score_;
  ThreadPool* thread_pool_;
};

#endif //FMLEARN_CORE_MODEL_H_

