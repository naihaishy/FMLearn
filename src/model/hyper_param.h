//
// Created by naihai on 2020/2/21.
// 存储所有的超参数

#ifndef FMLEARN_CORE_HYPER_PARAM_H_
#define FMLEARN_CORE_HYPER_PARAM_H_

#include <string>

#include "common/common.h"

struct TrainParam {
  int task = REGRESSION; // 0 for regression , 1 for classification
  int model = FM_MODEL; //  0 for linear model, 1 for fm model

  // acc prec recall f1 rmse mae auc
  // 当metric不为空时需要保证 验证数据valid_file 不为空
  std::string metric = "";

  std::string train_file;
  std::string valid_file;
  std::string model_file;

  int n_factors = 10;
  int n_epoch = 100;
  float learning_rate = 0.1;
  float reg_w0 = 0.1;
  float reg_W = 0.1;
  float reg_V = 0.1;
  float init_mean = 0.0;
  float init_stddev = 0.1;

  int n_thread = 1;
  long seed = 0l;

  // true交叉验证 交叉验证时使用train_file做切分 valid_file为空
  bool cross_validation = false;
  int num_folds = 5;

  bool early_stop = true;
  int stop_window = 3;

  bool norm = true;
  bool quiet = false;
  std::string to_string();
};

struct PredictionParam {

  std::string test_file;
  std::string model_file;
  std::string output_file;

  int n_thread = 1;

  bool norm = true;
  std::string to_string();
};

class HyperParam {
 public:
  HyperParam();
  TrainParam* GetTrainParam() const;
  PredictionParam* GetPredictionParam() const;

  bool is_train = true;

 private:
  TrainParam* train_param_ = nullptr;
  PredictionParam* prediction_param_ = nullptr;
};


#endif //FMLEARN_CORE_HYPER_PARAM_H_
