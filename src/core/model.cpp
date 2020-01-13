//
// Created by naihai on 2020/1/13.
//
#include "model.h"
#include "../common/common.h"
#include "../c_api/c_api_error.h"
#include <random>
#include <cassert>

inline float sigmoid(float x) {
  return 1.0f / (1.0f + expf(-x));
}

void FactorizationMachine::Fit(DMatrix* data, int epochs) {

  LOG_INFO("Start FactorizationMachine Fit")

  float lr = this->hyper_param_->learning_rate;
  float reg_w0 = this->hyper_param_->reg_w0;
  float reg_W = this->hyper_param_->reg_W;
  float reg_V = this->hyper_param_->reg_V;

  for (int epoch = 0; epoch < epochs; ++epoch) {
	LOG_INFO("epoch " + std::to_string(epoch))

	for (int m = 0; m < data->row_length; ++m) {
	  auto& x = data->rows[m];
	  auto inter_sum = new float[this->model_->n_factors_];

	  // predict
	  float y_pred = this->PredictInstance(x, inter_sum);
	  float y_true = data->labels[m];

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
		int& i = it.feature_id;
		float& xi = it.feature_val;
		float gradient_w = delta * xi;
		this->model_->W_[i] -= lr * (gradient_w + 2 * reg_W * this->model_->W_[i]);
	  }

	  for (int f = 0; f < this->model_->n_factors_; ++f) {
		for (auto& it : *x) {
		  int& i = it.feature_id;
		  float& xi = it.feature_val;
		  float& vif = this->model_->V_[i * this->model_->n_factors_ + f];
		  float gradient_v = delta * (xi * inter_sum[f] - vif * xi * xi);
		  vif -= lr * (gradient_v + 2 * reg_V * vif);
		}
	  }
	}
  }
}

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

float FactorizationMachine::PredictInstance(SparseRow* x, float* inter_sum) {
  float result = 0.0;
  result += this->model_->w0_;
  // linear term
  for (auto& it : *x) {
	result += this->model_->W_[it.feature_id] * it.feature_val;
  }
  // interaction term
  float inter1, inter2, d;
  for (int f = 0; f < this->model_->n_factors_; ++f) {
	inter1 = 0.0;
	inter2 = 0.0;
	if (nullptr != inter_sum) inter_sum[f] = 0.0;
	for (auto& it:*x) {
	  int& i = it.feature_id;
	  float& xi = it.feature_val;
	  float vif = this->model_->V_[i * this->model_->n_factors_ + f];
	  d = vif * xi;
	  inter1 += d;
	  inter2 += d * d;
	  if (nullptr != inter_sum) inter_sum[f] += d;
	}
	result += inter1 * inter1 - inter2;
  }
  return result;
}

FactorizationMachine::FactorizationMachine(int task,
										   int n_features,
										   int n_factors,
										   float lr,
										   float reg_w0,
										   float reg_W,
										   float reg_V,
										   float mean,
										   float stddev) {
  LOG_INFO("FactorizationMachine Construct Start!")
  this->model_ = new FMModel(task, n_features, n_factors, mean, stddev);
  this->hyper_param_ = new FMParam();
  this->hyper_param_->learning_rate = lr;
  this->hyper_param_->reg_w0 = reg_w0;
  this->hyper_param_->reg_W = reg_W;
  this->hyper_param_->reg_V = reg_V;
  LOG_INFO("FactorizationMachine Construct succeed!")
}

FactorizationMachine::~FactorizationMachine() {
  this->model_->Free();
  delete this->model_;
  delete this->hyper_param_;
  LOG_INFO("FactorizationMachine Deconstruct succeed")
}

void FMModel::InitWeights(float mean, float stddev) {
  try {
	// 分配内存
	this->W_ = new float[n_features_];
	this->V_ = new float[this->n_features_ * this->n_factors_];

	// 值初始化
	this->w0_ = 0.0;
	for (int i = 0; i < this->n_features_; ++i) {
	  this->W_[i] = 0.0;
	}
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	for (int i = 0; i < this->n_features_; ++i) {
	  for (int j = 0; j < this->n_factors_; ++j) {
		this->V_[i * n_factors_ + j] = distribution(generator);
	  }
	}
  } catch (std::bad_alloc& e) {
	LOG_INFO(e.what());
  }

  LOG_INFO("FMModel InitWeights succeed")
}

void FMModel::Free() {
  delete[] this->W_;
  delete[] this->V_;
  LOG_INFO("FMModel Free succeed")
}

