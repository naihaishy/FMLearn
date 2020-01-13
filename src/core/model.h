//
// Created by naihai on 2020/1/13.
//

#ifndef FMLEARN_CORE_MODEL_H_
#define FMLEARN_CORE_MODEL_H_

#include "../data/data.h"

#define REGRESSION 0
#define CLASSIFICATION 1
#define SQUARE_LOSS 0
#define CROSS_ENTROPY_LOSS 1

/**
 * FM 模型
 */
class FMModel {
 public:
  FMModel() {};
  ~FMModel() {};

  // 从checkpoint file中初始化模型
  explicit FMModel(const std::string& filename);

  /**
   * 初始化FMModel
   * @param task
   * @param n_features
   * @param n_factors
   * @param w0
   * @param W
   * @param V
   */
  explicit FMModel(int task, int n_features, int n_factors, float w0, float* W, float* V) :
	  task_(task), n_features_(n_features),
	  n_factors_(n_factors), w0_(w0), W_(W), V_(V) {};

  FMModel(int task, int n_features, int n_factors, float mean, float stddev) {
	this->task_ = task;
	this->n_features_ = n_features;
	this->n_factors_ = n_factors;
	this->InitWeights(mean, stddev);
  }

  void InitWeights(float mean, float stddev);
  void Free();

  int task_ = REGRESSION;
  int n_features_ = 0;
  int n_factors_ = 0;
  float w0_ = 0.0;
  float* W_ = nullptr;
  float* V_ = nullptr;
};

/**
 * FM 超参数
 */
struct FMParam {
  bool is_train = true;
  bool on_disk = false;
  bool quiet = false;

  // training
  float learning_rate = 0.1;
  float reg_w0 = 0.1;
  float reg_W = 0.1;
  float reg_V = 0.1;
  bool norm = true;
};

class FactorizationMachine {
 public:
  // Constructor and Destructor
  FactorizationMachine(int task, int n_features, int n_factors,
					   float lr, float reg_w0, float reg_W, float reg_V,
					   float mean, float stddev);

  ~FactorizationMachine();
  FactorizationMachine(const FactorizationMachine& other) = delete;
  void operator=(const FactorizationMachine&) = delete;

  void Fit(DMatrix* data, int epochs);
  void Predict(DMatrix* data, const float** out);

 private:

  float PredictInstance(SparseRow* x, float* inter_sum = nullptr);

  FMParam* hyper_param_;
  FMModel* model_;
};

#endif //FMLEARN_CORE_MODEL_H_
