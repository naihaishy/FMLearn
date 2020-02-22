//
// Created by naihai on 2020/1/29.
// 命令行参数有效性验证

#ifndef FMLEARN_CLI_VALIDATE_H_
#define FMLEARN_CLI_VALIDATE_H_

#include "common/log.h"
#include "common/utils.h"
#include "core/hyper_param.h"

class Validator {
 public:
  static bool Validate(TrainParam& param);
  static bool Validate(PredictionParam& param);
};

/**
 * 验证训练参数的有效性
 * @param param CliTrainParam
 * @return
 */
bool Validator::Validate(TrainParam& param) {
  if (!file_exists(param.train_file)) {
    LogError("train file " + param.train_file + " not exists");
    return false;
  }
  if (param.task != 0 && param.task != 1) {
    LogError(" -t <task> must be 0 or 1");
    return false;
  }
  if (param.model != 0 && param.model != 1) {
    LogError(" -m <model> must be 0 or 1");
    return false;
  }
  if (param.n_factors <= 0) {
    LogError(" -k <n_factors> must be greater than 0");
    return false;
  }
  if (param.n_epoch <= 0) {
    LogError(" -e <epoch_number> must be greater than 0");
    return false;
  }
  if (param.learning_rate < 0.0) {
    LogError("  -lr <learning_rate> must be greater than 0.0");
    return false;
  }
  if (param.init_mean < 0) {
    LogError(" -mean <init_mean> must be greater than or equal 0.0");
    return false;
  }
  if (param.init_stddev < 0) {
    LogError(" -stddev <init_stddev> must be greater than or equal 0.0");
    return false;
  }
  if (param.n_thread <= 0) {
    LogError(" -nt <thread_number> must be greater than 0");
    return false;
  }
  if (param.seed < 0) {
    LogError(" -seed <random_seed> must be greater than or equal 0");
    return false;
  }
  return true;
}

/**
 * 验证预测参数的有效性
 * @param param CliPredictionParam
 * @return
 */
bool Validator::Validate(PredictionParam& param) {
  if (!file_exists(param.test_file)) {
    LogError(" test_file not exists");
    return false;
  }
  if (!file_exists(param.model_file)) {
    LogError(" model_file not exists");
    return false;
  }
  return true;
}
#endif //FMLEARN_SRC_CLI_VALIDATE_H_
