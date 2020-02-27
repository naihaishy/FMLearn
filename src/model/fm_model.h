//
// Created by naihai on 2020/1/18.
//

#ifndef FMLEARN_CORE_FM_MODEL_H_
#define FMLEARN_CORE_FM_MODEL_H_

#include <limits>
#include <string>

#include "model/model.h"
#include "common/common.h"

/**
 * FM 模型 主要用于存储参数矩阵
 * Usage:
 *  FMMdoel *model = new FMModel();
 *  model.Initialize();
 *
 */
class FMModel : public Model {
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
      task_(task),
      n_features_(n_features),
      n_factors_(n_factors),
      w0_(w0),
      W_(W),
      V_(V) {};

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

  float& GetBias() { return w0_; }
  float*& GetW() { return W_; }
  float*& GetV() { return V_; }

 private:
  int task_ = REGRESSION;
  int model_ = FM_MODEL;
  int n_features_ = 0;
  int n_factors_ = 0;
  float w0_ = 0.0; // bias
  float* W_ = nullptr; // linear_weights
  float* V_ = nullptr; // intersection_weights

};

#endif //FMLEARN_CORE_FM_MODEL_H_
