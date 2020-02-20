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
  this->score_ = new FmScore();
  if (this->model_->GetTask() == REGRESSION) {
    this->loss_ = new SquaredLoss();
  } else {
    this->loss_ = new CrossEntropyLoss();
  }
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

  LogDebug("FactorizationMachine Construct succeed!");
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
  LogDebug("FactorizationMachine Deconstruct succeed");
}

/**
 * Fit
 * @param data
 * @param epochs
 * @param multi_thread
 */
void FactorizationMachine::Fit(DMatrix* data, int epochs, bool multi_thread, int n_threads) {
  LogDebug("Start FactorizationMachine Fit");
  LogDebug("FactorizationMachine Params: " + hyper_param_->to_string());

  if (model_->GetTask() == REGRESSION && model_->HasLimitPredict()) {
    model_->SetMaxTarget(data->max_label);
    model_->SetMinTarget(data->min_label);
  }

  if (multi_thread) {
    this->FitInMultiThread(data, epochs, n_threads);
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
    float norm = data->norms[m];
    // predict
    float y_pred = score_->Calculate(x, *model_, norm);
    results.emplace_back(y_pred);
  }
  return results;
}

/**
 *
 * @param data
 * @param epochs
 */
void FactorizationMachine::FitInSingleThread(DMatrix* data, int epochs) {

  for (int epoch = 0; epoch < epochs; ++epoch) {
    float ave_loss = loss_->CalGrad(data, model_);
    if (hyper_param_->verbose) {
      LogDebug("epoch " + std::to_string(epoch) +
          " loss: " + std::to_string(ave_loss));
    }
  }
}

void FMFitInSingleThread(const DMatrix* data,
                         FactorizationMachine* fm,
                         int start,
                         int end, float* loss) {

  Score* score = fm->GetScore();
  FMModel* model = fm->GetModel();
  FMHyperParam* param = fm->GetHyperParam();

  for (int m = start; m < end; ++m) {
    auto& x = data->rows[m];
    auto norm = data->norms[m];

    // predict instance
    float y_pred = score->Calculate(x, *model, norm);
    float y_true = data->labels[m];

    // calculate gradient and update weights
    float delta = y_pred - y_true;
    score->CalGrad(x, *model, norm, delta);

    // calculate loss
    (*loss) += 0.5f * (y_pred - y_true) * (y_pred - y_true);
  }
}

/**
 * 多线程训练
 *  每次迭代中 每个线程负责一部分数据进行训练
 *  等待所有线程训练完成 再开始下一次迭代
 * @param data
 * @param epochs
 */
void FactorizationMachine::FitInMultiThread(DMatrix* data, int epochs, int num_threads) {
  thread_pool_ = new ThreadPool(num_threads);

  int num_samples = data->row_length;
  int step = num_samples / num_threads + 1;

  for (int i = 0; i < epochs; ++i) {
    std::vector<float> losses = std::vector<float>(num_threads, 0.0);
    for (int j = 0; j < num_threads; ++j) {
      int start = j * step;
      int end = std::min(start + step, num_samples);
      thread_pool_->enqueue(std::bind(FMFitInSingleThread, data, this, start, end, &(losses[j])));
    }
    thread_pool_->Sync(num_threads);
    // 统计loss
    float loss_sum = 0.0;
    for (float loss:losses) loss_sum += loss;
    float ave_loss = loss_sum / num_samples;
    if (hyper_param_->verbose) {
      LogDebug("epoch " + std::to_string(i) +
          " loss: " + std::to_string(ave_loss));
    }
  }

}




