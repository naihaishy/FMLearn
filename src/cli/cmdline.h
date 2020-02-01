//
// Created by naihai on 2020/1/29.
// 命令行参数解析 解析结果为FMLearnCliParam
// -param value 例如 -lr 0.1 有参命令
// --long-param 例如 --quiet 无参命令

#ifndef FMLEARN_CLI_CMDLINE_H_
#define FMLEARN_CLI_CMDLINE_H_

#include <string>

#include "core/fm_param.h"

#include "cli/cli_param.h"

class CmdLine {
 public:
  CmdLine();
  ~CmdLine();

  void Help();
  bool Parse(int argc, char* argv[]);
  FMLearnCliParam* GetCliParam() const { return param_; };

  // Setter functions
  void SetTrain() { is_train_ = true; };
  void SetPredict() { is_train_ = false; };

 private:
  void ParseTrainParam(int argc, char* argv[]);
  void ParsePredictionParam(int argc, char* argv[]);

  bool is_train_; // training or prediction
  std::string training_help_str_;
  std::string predict_help_str_;
  FMLearnCliParam* param_;
};

#endif //FMLEARN_CLI_CMDLINE_H_
