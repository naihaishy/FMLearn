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
                   float w0, float* W, float* V) :
      task_(task),
      n_features_(n_features), n_factors_(n_factors),
      w0_(w0), W_(W), V_(V) {};

  FMModel(int task, int n_features, int n_factors,
          float mean, float stddev);

  explicit FMModel(const std::string &model_file);

  void InitWeights(float mean, float stddev);
  void Free();
  void Save(const std::string& filename);
  bool Load(const std::string& filename);

  int task_ = REGRESSION;
  int n_features_ = 0;
  int n_factors_ = 0;
  float w0_ = 0.0;
  float* W_ = nullptr;
  float* V_ = nullptr;

  // 是否对predict结果进行范围限制 在task==REGRESSION情况下有效
  bool limit_predict = false;
  float min_target_ = 0.0;
  float max_target_ = 0.0;
};

#endif //FMLEARN_CORE_FM_MODEL_H_
