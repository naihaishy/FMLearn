//
// Created by naihai on 2020/1/13.
//

#ifndef FMLEARN_CORE_MODEL_H_
#define FMLEARN_CORE_MODEL_H_

#include "common/common.h"
#include "data/data.h"
#include "loss/loss.h"
#include "score/score.h"

#include "core/fm_model.h"
#include "core/fm_param.h"

// Entry class for FM FM的入口类
class FactorizationMachine {
 public:
  // Constructor and Destructor
  FactorizationMachine(int task, int n_features, int n_factors,
                       float lr, float reg_w0, float reg_W, float reg_V,
                       float mean, float stddev,
                       bool norm, bool verbose);

  /**
   * 从模型文件中构建FactorizationMachine
   * @param model_file FMModel 对象参数文件
   */
  explicit FactorizationMachine(const std::string &model_file);

  ~FactorizationMachine();
  FactorizationMachine(const FactorizationMachine& other) = delete;
  void operator=(const FactorizationMachine&) = delete;

  void Initialize();

  void Fit(DMatrix* data, int epochs, bool multi_thread=false);

  std::vector<float> Predict(DMatrix* data);

  FMHyperParam* GetHyperParam();
  FMModel* GetModel();

  friend void FMFitInSingleThread(DMatrix* data, FactorizationMachine* fm,
                                  int epochs, int start, int end);

 private:
  float PredictInstance(SparseRow* x, float norm = 1.0, float* inter_sum = nullptr);
  // void FitInMultiThread(DMatrix* data, int epochs);
  void FitInSingleThread(DMatrix* data, int epochs);
  FMHyperParam* hyper_param_;
  FMModel* model_;
  // ThreadPool* thread_pool_;

  Loss *loss_;
  Score *score_;
};

#endif //FMLEARN_CORE_MODEL_H_

