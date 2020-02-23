//
// Created by naihai on 2020/1/18.
//

#ifndef FMLEARN_CORE_FM_MODEL_H_
#define FMLEARN_CORE_FM_MODEL_H_

#include <limits>
#include <string>

#include "common/common.h"

/**
 * FM 模型 主要用于存储参数矩阵
 * Usage:
 *  FMMdoel *model = new FMModel();
 *  model.Initialize();
 *
 */
class FMModel {
 public:
  FMModel() = default;
  ~FMModel();

  void Initialize();

  explicit FMModel(int task,
                   int n_features,
                   int n_factors,
                   float w0,
                   float* W,
                   float* V) :
      task_(task), n_features_(n_features), n_factors_(n_factors),
      w0_(w0), W_(W), V_(V) {};

  FMModel(int task,
          int n_features,
          int n_factors,
          float mean,
          float stddev);

  // 从checkpoint file中初始化模型
  explicit FMModel(const std::string& model_file);

  void InitWeights(float mean, float stddev);
  void Reset();
  void Free();
  void Save(const std::string& filename);
  bool Load(const std::string& filename);

  // Getter Functions
  int GetTask() const { return task_; }
  int GetModel() const { return model_; }
  int GetNumFeatures() const { return n_features_; }
  int GetNumFactors() const { return n_factors_; }
  bool HasLimitPredict() const { return limit_predict; }
  float GetMaxTarget() const { return max_target_; }
  float GetMinTarget() const { return min_target_; }

  float& GetBias() { return w0_; }
  float*& GetW() { return W_; }
  float*& GetV() { return V_; }

  // Setter Functions
  void SetMaxTarget(float value) { max_target_ = value; }
  void SetMinTarget(float value) { min_target_ = value; }

 private:
  int task_ = REGRESSION;
  int model_ = FM_MODEL;
  int n_features_ = 0;
  int n_factors_ = 0;
  float w0_ = 0.0; // bias
  float* W_ = nullptr; // linear_weights
  float* V_ = nullptr; // intersection_weights

  // 是否对predict结果进行范围限制 在task==REGRESSION情况下有效
  bool limit_predict = false;
  float min_target_ = 0.0;
  float max_target_ = 0.0;
};

#endif //FMLEARN_CORE_FM_MODEL_H_
