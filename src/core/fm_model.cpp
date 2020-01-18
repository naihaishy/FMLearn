//
// Created by naihai on 2020/1/18.
//

#include "fm_model.h"
#include <random>

FMModel::FMModel(int task, int n_features, int n_factors,
                 float mean, float stddev) {
  FMModel(task,
          n_features, n_factors,
          mean, stddev,
          std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
}

FMModel::FMModel(int task,
                 int n_features, int n_factors,
                 float mean, float stddev,
                 float max_target, float min_target) {
  this->task_ = task;
  this->n_features_ = n_features;
  this->n_factors_ = n_factors;
  this->max_target_ = max_target;
  this->min_target_ = min_target;
  this->InitWeights(mean, stddev);
}

void FMModel::InitWeights(float mean, float stddev) {
  // 分配内存
  this->W_ = new float[n_features_];
  this->V_ = new float[this->n_features_ * this->n_factors_];

  // 值初始化
  this->w0_ = 0.0;
  for (int i = 0; i < this->n_features_; ++i) {
    this->W_[i] = 0.0;
  }
  std::default_random_engine generator{};
  std::uniform_real_distribution<float> distribution(0.0, 1.0);

  for (int i = 0; i < this->n_features_; ++i) {
    for (int j = 0; j < this->n_factors_; ++j) {
      this->V_[i * n_factors_ + j] = distribution(generator);
    }
  }

  LOG_INFO("FMModel InitWeights succeed")
}

void FMModel::Free() {
  delete[] this->W_;
  delete[] this->V_;
  LOG_INFO("FMModel Free succeed")
}

