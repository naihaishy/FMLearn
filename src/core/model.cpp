//
// Created by naihai on 2020/1/13.
//
#include "model.h"
#include "src/c_api/c_api_error.h"

#include <random>
#include <memory.h>
#include "src/common/log.h"
#include <cmath>
inline float sigmoid(float x) {
  return 1.0f / (1.0f + expf(-x));
}

FactorizationMachine::FactorizationMachine(int task,
                                           int n_features, int n_factors,
                                           float lr,
                                           float reg_w0, float reg_W, float reg_V,
                                           float mean, float stddev,
                                           bool norm, bool verbose) {
  this->model_ = new FMModel(task, n_features, n_factors, mean, stddev);
  this->hyper_param_ = new FMHyperParam(lr, reg_w0, reg_W, reg_V, norm, verbose);
  Logging::debug("FactorizationMachine Construct succeed!");
}

FactorizationMachine::~FactorizationMachine() {
  this->model_->Free();
  delete this->model_;
  delete this->hyper_param_;
  Logging::debug("FactorizationMachine Deconstruct succeed");
}
FMHyperParam* FactorizationMachine::GetHyperParam() {
  return this->hyper_param_;
}
FMModel* FactorizationMachine::GetModel() {
  return this->model_;
}

void FactorizationMachine::Fit(DMatrix* data, int epochs) {
  Logging::debug("Start FactorizationMachine Fit");
  Logging::debug("FactorizationMachine Params: " + hyper_param_->to_string());
  if (this->model_->task_ == REGRESSION && this->model_->limit_predict) {
    this->model_->min_target_ = data->min_label;
    this->model_->max_target_ = data->max_label;
  }

  float lr = this->hyper_param_->learning_rate;
  float reg_w0 = this->hyper_param_->reg_w0;
  float reg_W = this->hyper_param_->reg_W;
  float reg_V = this->hyper_param_->reg_V;
  bool use_norm = this->hyper_param_->norm;

  Logging::debug("data nums " + std::to_string(data->row_length));
  int K = this->model_->n_factors_;
  auto inter_sum = new float[K];
  for (int i = 0; i < K; ++i) inter_sum[i] = 0.0;

  for (int epoch = 0; epoch < epochs; ++epoch) {
    float losses = 0.0;
    for (int m = 0; m < data->row_length; ++m) {
      auto& x = data->rows[m];
      auto norm = data->norms[m];
      if (!use_norm) norm = 1.0;
      for (int i = 0; i < K; ++i) inter_sum[i] = 0.0;

      // predict
      float y_pred = this->PredictInstance(x, norm, inter_sum);
      float y_true = data->labels[m];
      // LOG_INFO("y_pred " + std::to_string(y_pred) + "\t y_true :" + std::to_string(y_true))

      // calculate gradient
      float delta = 0.0;
      if (this->model_->task_ == REGRESSION) {
        delta = y_pred - y_true;
      } else if (this->model_->task_ == CLASSIFICATION) {
        delta = (sigmoid(y_true * y_pred) - 1) * y_true;
      } else {
        throw std::exception();
      }

      // update weights
      this->model_->w0_ -= lr * (delta + 2 * reg_w0 * this->model_->w0_);

      for (auto& it:*x) {
        int i = it.feature_id;
        float xi = it.feature_val;
        xi = xi * norm;
        float gradient_w = delta * xi;
        this->model_->W_[i] -= lr * (gradient_w + 2 * reg_W * this->model_->W_[i]);
      }

      for (int f = 0; f < K; ++f) {
        for (auto& it : *x) {
          int& i = it.feature_id;
          float& xi = it.feature_val;
          float& vif = this->model_->V_[i * K + f];
          float gradient_v = delta * (xi * inter_sum[f] - vif * xi * xi);
          vif -= lr * (gradient_v + 2 * reg_V * vif);
        }
      }

      // calculate loss
      if (this->model_->task_ == REGRESSION) {
        losses += 0.5f * (y_pred - y_true) * (y_pred - y_true);
      } else if (this->model_->task_ == CLASSIFICATION) {
        losses += -log(sigmoid(y_true * y_pred));
      }
    }

    if (this->hyper_param_->verbose) {
      Logging::debug("epoch " + std::to_string(epoch) +
          " loss: " + std::to_string(losses / data->row_length));
    }
  }

  delete[] inter_sum;
}

/**
 * 预测
 * @param data DMatrix
 * @param out
 */
void FactorizationMachine::Predict(DMatrix* data, const float** out) {
  std::vector<float> results;
  results.reserve(data->row_length);
  for (int m = 0; m < data->row_length; ++m) {
    auto& x = data->rows[m];
    // predict
    float y_pred = this->PredictInstance(x);
    results.emplace_back(y_pred);
  }
  *out = &results[0];
}

/**
 * 预测单个样本
 * @param x 样本
 * @param inter_sum float*指针 参数更新时的中间值数组
 * @return
 */
float FactorizationMachine::PredictInstance(SparseRow* x, float norm, float* inter_sum) {
  float result = 0.0;
  result += this->model_->w0_;
  // linear term
  for (auto& it : *x) {
    int i = it.feature_id;
    float xi = it.feature_val;
    result += this->model_->W_[i] * xi * norm;
  }
  // interaction term
  int K = this->model_->n_factors_;
  float inter1, inter2, d;
  for (int f = 0; f < K; ++f) {
    inter1 = 0.0;
    inter2 = 0.0;
    if (nullptr != inter_sum) inter_sum[f] = 0.0;
    for (auto& it:*x) {
      int i = it.feature_id;
      float xi = it.feature_val;
      xi = xi * norm;
      float vif = this->model_->V_[i * K + f];
      d = vif * xi;
      inter1 += d;
      inter2 += d * d;
      if (nullptr != inter_sum) inter_sum[f] += d;
    }
    result += inter1 * inter1 - inter2;
  }

  if (this->model_->task_ == REGRESSION && this->model_->limit_predict) {
    result = std::max(this->model_->min_target_, result);
    result = std::min(this->model_->max_target_, result);
  }
  return result;
}

/**
 * 对DMatrix中[start, end)行部分数据进行单线程训练
 * @param data  DMatrix
 * @param epochs
 * @param start 开始行数 include
 * @param end  结束行数 exclude
 */
static void FMFitInSingleThread(DMatrix* data, FactorizationMachine* fm,
                                int epochs, int start, int end) {


}
/**
 * 多线程进行训练
 * @param data
 * @param epochs
 */
void FactorizationMachine::FitInMultiThread(DMatrix* data, int epochs) {

}

