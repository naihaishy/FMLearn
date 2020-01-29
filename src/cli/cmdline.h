//
// Created by naihai on 2020/1/29.
// 命令行参数解析 解析结果为FMLearnCliParam
// -param value 例如 -lr 0.1 有参命令
// --long-param 例如 --quiet 无参命令

#ifndef FMLEARN_CLI_CMDLINE_H_
#define FMLEARN_CLI_CMDLINE_H_
#include <vector>
#include <string>
#include <unordered_map>
#include <src/core/fm_param.h>

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

  std::string file_format = "csv"; // csv txt
  std::string file_sep = ","; // , for csv
  bool norm = true;
  bool quiet = true;
};

struct CliPredictionParam {
  std::string test_file;
  std::string model_file;
  std::string output_file;

  int n_thread = 1;

  std::string file_format = "csv"; // csv txt
  std::string file_sep = ","; // , for csv
  bool norm = true;
};

class FMLearnCliParam {
 public:
  bool is_train = true;
  CliTrainParam* GetTrainParam();
  CliPredictionParam* GetPredictionParam();
 private:
  CliTrainParam* train_param_ = nullptr;
  CliPredictionParam* prediction_param_ = nullptr;
};

class CmdLine {

 public:
  CmdLine();
  ~CmdLine();

  void Help();
  void SetTrain() { is_train = true; };
  void SetPredict() { is_train = false; };
  bool Parse(int argc, char* argv[]);
  FMLearnCliParam* GetCliParam() { return param_; };

 private:

  void ParseTrainParam(int argc, char* argv[]);
  void ParsePredictionParam(int argc, char* argv[]);

  std::string training_help_str_;
  std::string predict_help_str_;
  bool is_train; // training or prediction

  FMLearnCliParam* param_;
};

#endif //FMLEARN_CLI_CMDLINE_H_
