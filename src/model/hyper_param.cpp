//
// Created by naihai on 2020/2/22.
//

#include "model/hyper_param.h"

std::string TrainParam::to_string() {
  std::string result;
  // result.reserve(1024 * 4);
  result.append("TrainParam: \n");
  result.append("task            : " + std::to_string(task) + "\n");
  result.append("model           : " + std::to_string(model) + "\n");
  result.append("metric          : " + metric + "\n");
  result.append("train_file      : " + train_file + "\n");
  result.append("validation_file : " + valid_file + "\n");
  result.append("model_file      : " + model_file + "\n");
  result.append("n_factors       : " + std::to_string(n_factors) + "\n");
  result.append("n_epoch         : " + std::to_string(n_epoch) + "\n");
  result.append("learning_rate   : " + std::to_string(learning_rate) + "\n");
  result.append("reg_w0          : " + std::to_string(reg_w0) + "\n");
  result.append("reg_W           : " + std::to_string(reg_W) + "\n");
  result.append("reg_V           : " + std::to_string(reg_V) + "\n");
  result.append("init_mean       : " + std::to_string(init_mean) + "\n");
  result.append("init_stddev     : " + std::to_string(init_stddev) + "\n");
  result.append("n_thread        : " + std::to_string(n_thread) + "\n");
  result.append("seed            : " + std::to_string(seed) + "\n");
  result.append("cross_validation: " + std::to_string(cross_validation) + "\n");
  result.append("num_folds       : " + std::to_string(num_folds) + "\n");
  result.append("early_stop      : " + std::to_string(early_stop) + "\n");
  result.append("stop_window     : " + std::to_string(stop_window) + "\n");
  result.append("norm            : " + std::to_string(norm) + "\n");
  result.append("quiet           : " + std::to_string(quiet) + "\n");
  return result;
}

std::string PredictionParam::to_string() {
  std::string result;
  result.reserve(1024);
  result.append("PredictionParam: \n");
  result.append("test_file        : " + test_file + "\n");
  result.append("model_file       : " + model_file + "\n");
  result.append("output_file      : " + output_file + "\n");
  result.append("n_thread         : " + std::to_string(n_thread) + "\n");
  result.append("seed             : " + std::to_string(norm) + "\n");
  return result;
}

TrainParam* HyperParam::GetTrainParam() const {
  return is_train ? train_param_ : nullptr;
}

PredictionParam* HyperParam::GetPredictionParam() const {
  return !is_train ? prediction_param_ : nullptr;
}

HyperParam::HyperParam() {
  train_param_ = new TrainParam();
  prediction_param_ = new PredictionParam();
}

