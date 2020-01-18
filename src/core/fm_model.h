//
// Created by naihai on 2020/1/18.
//

#ifndef FMLEARN_CORE_FM_MODEL_H_
#define FMLEARN_CORE_FM_MODEL_H_

#include <limits>
#include "src/common/common.h"

/**
 * FM 模型
 * 主要用于存储参数矩阵
 */
class FMModel {
 public:
  FMModel() = default;;
  ~FMModel() = default;;

  // 从checkpoint file中初始化模型
  // explicit FMModel(const std::string& filename);

  explicit FMModel(int task,
                   int n_features, int n_factors,
                   float max_target, float min_target,
                   float w0, float* W, float* V) :
      task_(task),
      n_features_(n_features), n_factors_(n_factors),
      max_target_(max_target), min_target_(min_target),
      w0_(w0), W_(W), V_(V) {};

  FMModel(int task, int n_features, int n_factors,
          float mean, float stddev,
          float max_target, float min_target);

  FMModel(int task, int n_features, int n_factors,
          float mean, float stddev);

  void InitWeights(float mean, float stddev);
  void Free();

  int task_ = REGRESSION;
  int n_features_ = 0;
  int n_factors_ = 0;
  float w0_ = 0.0;
  float* W_ = nullptr;
  float* V_ = nullptr;

  float min_target_ = std::numeric_limits<float>::max();
  float max_target_ = std::numeric_limits<float>::min();
};

#endif //FMLEARN_CORE_FM_MODEL_H_
