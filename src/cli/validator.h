//
// Created by naihai on 2020/1/29.
// 命令行参数有效性验证

#ifndef FMLEARN_CLI_VALIDATE_H_
#define FMLEARN_CLI_VALIDATE_H_

#include "common/log.h"
#include "common/utils.h"

class Validator {
 public:
  static bool Validate(CliTrainParam& param);
  static bool Validate(CliPredictionParam& param);
};

bool Validator::Validate(CliTrainParam& param) {
  if (!file_exists(param.train_file)) {
    Logging::error(" train_file not exists");
    return false;
  }
  if (param.task != 0 && param.task != 1) {
    Logging::error(" -t <task> must be 0 or 1");
    return false;
  }
  if (param.model != 0 && param.model != 1) {
    Logging::error(" -m <model> must be 0 or 1");
    return false;
  }
  if (param.n_factors <= 0) {
    Logging::error(" -k <n_factors> must be greater than 0");
    return false;
  }
  if (param.n_epoch <= 0) {
    Logging::error(" -e <epoch_number> must be greater than 0");
    return false;
  }
  if (param.learning_rate < 0.0) {
    Logging::error("  -lr <learning_rate> must be greater than 0.0");
    return false;
  }
  if (param.init_mean < 0) {
    Logging::error(" -mean <init_mean> must be greater than or equal 0.0");
    return false;
  }
  if (param.init_stddev < 0) {
    Logging::error(" -stddev <init_stddev> must be greater than or equal 0.0");
    return false;
  }
  if (param.n_thread <= 0) {
    Logging::error(" -nt <thread_number> must be greater than 0");
    return false;
  }
  if (param.seed < 0) {
    Logging::error(" -seed <random_seed> must be greater than or equal 0");
    return false;
  }
  return true;
}

bool Validator::Validate(CliPredictionParam& param) {
  if (!file_exists(param.test_file)) {
    Logging::error(" test_file not exists");
    return false;
  }
  if (!file_exists(param.model_file)) {
    Logging::error(" model_file not exists");
    return false;
  }
  return true;
}
#endif //FMLEARN_SRC_CLI_VALIDATE_H_
