//
// Created by naihai on 2020/1/13.
//

#include "core/model.h"

#include <cmath>

#include "c_api/c_api_error.h"
#include "common/log.h"
#include "loss/squared_loss.h"
#include "loss/cross_entropy_loss.h"
#include "score/fm_score.h"

inline float sigmoid(float x) {
  return 1.0f / (1.0f + expf(-x));
}

FactorizationMachine::FactorizationMachine(const std::string& model_file) {
  this->model_ = new FMModel(model_file);
  this->hyper_param_ = nullptr;
}

FactorizationMachine::FactorizationMachine(int task,
                                           int n_features, int n_factors,
                                           float lr,
                                           float reg_w0, float reg_W, float reg_V,
                                           float mean, float stddev,
                                           bool norm, bool verbose) {
  this->model_ = new FMModel(task, n_features, n_factors, mean, stddev);
  this->hyper_param_ = new FMHyperParam(lr, reg_w0, reg_W, reg_V, norm, verbose);

  this->score_ = new FmScore();
  if (task == REGRESSION) {
    this->loss_ = new SquaredLoss();
  } else {
    this->loss_ = new CrossEntropyLoss();
  }

  Logging::debug("FactorizationMachine Construct succeed!");
}

/**
 * 初始化
 */
void FactorizationMachine::Initialize() {

}

FactorizationMachine::~FactorizationMachine() {
  this->model_->Free();
  delete this->model_;
  delete this->hyper_param_;
  Logging::debug("FactorizationMachine Deconstruct succeed");
}

FMHyperParam* FactorizationMachine::GetHyperParam() const {
  return this->hyper_param_;
}
FMModel* FactorizationMachine::GetModel() const {
  return this->model_;
}

/**
 * Fit
 * @param data
 * @param epochs
 * @param multi_thread
 */
void FactorizationMachine::Fit(DMatrix* data, int epochs, bool multi_thread) {
  Logging::debug("Start FactorizationMachine Fit");
  Logging::debug("FactorizationMachine Params: " + hyper_param_->to_string());
  if (model_->GetTask() == REGRESSION && model_->HasLimitPredict()) {
    model_->SetMaxTarget(data->max_label);
    model_->SetMinTarget(data->min_label);
  }
  if (multi_thread) {
    // this->FitInMultiThread(data, epochs);
  } else {
    this->FitInSingleThread(data, epochs);
  }

}

/**
 * 预测
 * @param data DMatrix
 * @param out
 */
std::vector<float> FactorizationMachine::Predict(DMatrix* data) {
  std::vector<float> results;
  results.reserve(data->row_length);
  for (int m = 0; m < data->row_length; ++m) {
    auto& x = data->rows[m];
    // predict
    float y_pred = this->PredictInstance(x);
    results.emplace_back(y_pred);
  }
  return results;
}

/**
 * 预测单个样本
 * @param x 样本
 * @param inter_sum float*指针 参数更新时的中间值数组
 * @return
 */
float FactorizationMachine::PredictInstance(SparseRow* x, float norm, float* inter_sum) {
  float result = 0.0;

  float w0 = model_->GetBias();
  float* W = model_->GetW();
  float* V = model_->GetV();

  result += w0;
  // linear term
  for (auto& it : *x) {
    int i = it.feature_id;
    float xi = it.feature_val;
    result += W[i] * xi * norm;
  }
  // interaction term
  int K = model_->GetNumFactors();
  float inter1, inter2, d;
  for (int f = 0; f < K; ++f) {
    inter1 = 0.0;
    inter2 = 0.0;
    if (nullptr != inter_sum) inter_sum[f] = 0.0;
    for (auto& it:*x) {
      int i = it.feature_id;
      float xi = it.feature_val;
      xi = xi * norm;
      float vif = V[i * K + f];
      d = vif * xi;
      inter1 += d;
      inter2 += d * d;
      if (nullptr != inter_sum) inter_sum[f] += d;
    }
    result += inter1 * inter1 - inter2;
  }

  if (model_->GetTask() == REGRESSION && model_->HasLimitPredict()) {
    result = std::max(model_->GetMinTarget(), result);
    result = std::min(model_->GetMaxTarget(), result);
  }
  return result;
}

/**
 *
 * @param data
 * @param epochs
 */
void FactorizationMachine::FitInSingleThread(DMatrix* data, int epochs) {

  Logging::debug("data nums " + std::to_string(data->row_length));

  for (int epoch = 0; epoch < epochs; ++epoch) {
    float ave_loss = loss_->CalGrad(data, model_, hyper_param_, score_);

    if (hyper_param_->verbose) {
      Logging::debug("epoch " + std::to_string(epoch) +
          " loss: " + std::to_string(ave_loss));
    }
  }
}




