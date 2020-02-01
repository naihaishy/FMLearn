//
// Created by naihai on 2020/1/30.
// command line parameter

#ifndef FMLEARN_CLI_CLI_PARAM_H_
#define FMLEARN_CLI_CLI_PARAM_H_

#include <string>

struct CliTrainParam {
  int task = 0; // 0 for regression , 1 for classification
  int model = 1; //  0 for linear model, 1 for fm model

  std::string train_file;
  std::string validation_file;
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

  bool norm = true;
  bool quiet = false;
  std::string to_string();
};

struct CliPredictionParam {
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
  bool is_train = true;
  CliTrainParam* GetTrainParam();
  CliPredictionParam* GetPredictionParam();
 private:
  CliTrainParam* train_param_ = nullptr;
  CliPredictionParam* prediction_param_ = nullptr;
};


#endif //FMLEARN_CLI_CLI_PARAM_H_
