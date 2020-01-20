//
// Created by naihai on 2020/1/13.
//

#ifndef FMLEARN_CORE_MODEL_H_
#define FMLEARN_CORE_MODEL_H_

#include "src/data/data.h"
#include "src/common/common.h"
#include "src/core/fm_model.h"
#include "src/core/fm_param.h"

// Entry class for FM FM的入口类
class FactorizationMachine {
 public:
  // Constructor and Destructor
  FactorizationMachine(int task, int n_features, int n_factors,
                       float lr, float reg_w0, float reg_W, float reg_V,
                       float mean, float stddev,
                       bool norm, bool verbose);

  ~FactorizationMachine();
  FactorizationMachine(const FactorizationMachine& other) = delete;
  void operator=(const FactorizationMachine&) = delete;

  void Fit(DMatrix* data, int epochs);
  void Predict(DMatrix* data, const float** out);

  FMHyperParam* GetHyperParam();
  FMModel* GetModel();

 private:
  float PredictInstance(SparseRow* x, float norm = 1.0, float* inter_sum = nullptr);
  FMHyperParam* hyper_param_;
  FMModel* model_;
};

#endif //FMLEARN_CORE_MODEL_H_

