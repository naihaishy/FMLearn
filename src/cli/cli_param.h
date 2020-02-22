//
// Created by naihai on 2020/1/30.
// command line parameter

#ifndef FMLEARN_CLI_CLI_PARAM_H_
#define FMLEARN_CLI_CLI_PARAM_H_

#include <string>

#include "common/common.h"

struct CliTrainParam {
  int task = REGRESSION; // 0 for regression , 1 for classification
  int model = FM_MODEL; //  0 for linear model, 1 for fm model

  std::string train_file;
  std::string valid_file;
  std::string model_file;
  std::string metric = ""; // acc prec recall f1 rmse mae auc

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
  bool cross_validation = false; //
  int num_folds = 5;

  bool early_stop = true;
  int stop_window = 3;

  bool norm = true;
  bool quiet = false;
  std::string to_string();
};

struct CliPredictionParam {
  int task = REGRESSION; // 0 for regression , 1 for classification
  int model = FM_MODEL; //  0 for linear model, 1 for fm model

  std::string test_file;
  std::string model_file;
  std::string output_file;

  int n_thread = 1;

  bool norm = true;
  std::string to_string();
};

class FMLearnCliParam {
 public:
  FMLearnCliParam();
  CliTrainParam* GetTrainParam() const;
  CliPredictionParam* GetPredictionParam() const;

  bool IsTrain() const { return is_train_; }
  void SetTrain() { is_train_ = true; }

 private:
  CliTrainParam* train_param_ = nullptr;
  CliPredictionParam* prediction_param_ = nullptr;
  bool is_train_ = false;
};

#endif //FMLEARN_CLI_CLI_PARAM_H_
