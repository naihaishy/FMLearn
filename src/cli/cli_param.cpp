//
// Created by naihai on 2020/1/30.
//
#include "cli_param.h"

std::string CliTrainParam::to_string() {
  std::string result;
  // result.reserve(1024 * 4);
  result.append("CliTrainParam: \n");
  result.append("task            : " + std::to_string(task) + "\n");
  result.append("model           : " + std::to_string(model) + "\n");
  result.append("train_file      : " + train_file + "\n");
  result.append("validation_file : " + validation_file + "\n");
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
  result.append("norm            : " + std::to_string(norm) + "\n");
  result.append("quiet           : " + std::to_string(quiet) + "\n");
  return result;
}

std::string CliPredictionParam::to_string() {
  std::string result;
  result.reserve(1024);
  result.append("CliPredictionParam: \n");
  result.append("test_file        : " + test_file + "\n");
  result.append("model_file       : " + model_file + "\n");
  result.append("output_file      : " + output_file + "\n");
  result.append("n_thread         : " + std::to_string(n_thread) + "\n");
  result.append("seed             : " + std::to_string(norm) + "\n");
  return result;
}

CliTrainParam* FMLearnCliParam::GetTrainParam() {
  return is_train ? train_param_ : nullptr;
}

CliPredictionParam* FMLearnCliParam::GetPredictionParam() {
  return !is_train ? prediction_param_ : nullptr;
}

FMLearnCliParam::FMLearnCliParam() {
  train_param_ = new CliTrainParam();
  prediction_param_ = new CliPredictionParam();
}


