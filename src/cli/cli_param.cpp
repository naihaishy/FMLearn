//
// Created by naihai on 2020/1/30.
//
#include "cli_param.h"

std::string CliTrainParam::to_string() {
  std::string result;
  result.reserve(1024 * 4);
  result.append("task :" + std::to_string(task) + "\t");
  result.append("model :" + std::to_string(model) + "\t");
  result.append("train_file :" + train_file + "\t");
  result.append("validation_file :" + validation_file + "\t");
  result.append("model_file :" + model_file + "\t");
  result.append("n_factors :" + std::to_string(n_factors) + "\t");
  result.append("n_epoch :" + std::to_string(n_epoch) + "\t");
  result.append("learning_rate :" + std::to_string(learning_rate) + "\t");
  result.append("reg_w0 :" + std::to_string(reg_w0) + "\t");
  result.append("reg_W :" + std::to_string(reg_W) + "\t");
  result.append("reg_V :" + std::to_string(reg_V) + "\t");
  result.append("init_mean :" + std::to_string(init_mean) + "\t");
  result.append("init_stddev :" + std::to_string(init_stddev) + "\t");
  result.append("n_thread :" + std::to_string(n_thread) + "\t");
  result.append("seed :" + std::to_string(seed) + "\t");
  result.append("file_format :" + file_format + "\t");
  result.append("file_sep :" + std::string(1, file_sep) + "\t");
  result.append("norm :" + std::to_string(norm) + "\t");
  result.append("quiet :" + std::to_string(quiet) + "\t");
  return result;
}

std::string CliPredictionParam::to_string() {
  std::string result;
  result.reserve(1024);
  result.append("test_file :" + test_file + "\t");
  result.append("model_file :" + model_file + "\t");
  result.append("output_file :" + output_file + "\t");
  result.append("n_thread :" + std::to_string(n_thread) + "\t");
  result.append("file_format :" + file_format + "\t");
  result.append("file_sep :" + std::string(1, file_sep) + "\t");
  result.append("seed :" + std::to_string(norm) + "\t");
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


