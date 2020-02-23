//
// Created by naihai on 2020/1/29.
//

#include "cli/cmdline.h"

#include "common/utils.h"
#include "common/log.h"

#include "model/validator.h"

/**
 * 帮助 显示所有参数
 */
void CmdLine::Help() {
  if (is_train_) {
    printf("%s\n", training_help_str_.c_str());
  } else {
    printf("%s\n", predict_help_str_.c_str());
  }
}

CmdLine::CmdLine() {

  training_help_str_ = std::string(R"(
------------------------------ Training task ------------------------------
USAGE:
     fmlearn_train train_file model_file [OPTIONS]

OPTIONS:
  -t <task>            : 0 for regression , 1 for classification

  -m <model>           : 0 for linear model, 1 for fm model, default 1

  -me <metric>     : metric for evaluation, support acc, prec, recall, default none

  -v <validate_file>   :  Path of the validation data file. Empty by default,

  -k <n_factors>       :  Number of the latent factor used by fm and ffm tasks. Using 4 by default.

  -e <epoch_number>    :  Number of epoch for training. Using 100 by default.

  -lr <learning_rate>  :  Learning rate for stochastic gradient descent. Using 0.2 by default.

  -reg <lambda>        :  Lambda for L2 regular (reg_w0, reg_W, reg_V). One value to indicate all,
                          or use '|' to separate (0.01|0.02|0.01), Using 0.002 by default.

  -mean <init_mean>    : Initialize mean for fm model, 0.0 by default

  -stddev <init_stddev>: Initialize stddev for fm model, 0.1 by default

  -nt <thread_number>  :  Number of thread for multi-thread training.

  -seed <random_seed>  :  Random Seed to shuffle training data set. 0 by default.

  --no-norm            :  Disable instance-wise normalization. By default, FMLearn will use
                          instance-wise normalization for training.
  --quiet              :  Quiet mode, don't output any log information during training. True by default.

---------------------------------------------------------------------------)");

  predict_help_str_ = std::string(R"(
------------------------------ Prediction task ------------------------------
USAGE:
     fmlearn_predict test_file model_file [OPTIONS]

OPTIONS:

  -o <output_file>     :  Path of the output file. On default, this value will be set
                              to 'test_file' + '.out'
  -nt <thread number>  :  Number of thread for multi-thread learning.

  --no-norm            :  Disable instance-wise normalization. By default, FMLearn will use
                          instance-wise normalization for prediction.

-----------------------------------------------------------------------------)");
  param_ = new HyperParam();
  is_train_ = true;
}

/**
 * 解析命令行参数
 * @param argc
 * @param argv
 */
bool CmdLine::Parse(int argc, char** argv) {
  if (argc == 1) {
    Help();
    exit(0);
  }
  if (argc < 3) {
    LogError("Invalid Input parameter");
    return false;
  }

  // important!
  param_->is_train = is_train_;

  if (is_train_) {
    // parse training parameter
    LogInfo("Parse training parameter");
    try {
      ParseTrainParam(argc, argv);
      if (!Validator::Validate(*param_->GetTrainParam())) {
        LogError("Validate command line train parameter failed");
        return false;
      }
    } catch (std::exception& e) {
      LogError(e.what());
      return false;
    }
  } else {
    // parse prediction parameter
    LogInfo("Parse prediction parameter");
    try {
      ParsePredictionParam(argc, argv);
      if (!Validator::Validate(*param_->GetPredictionParam())) {
        LogError("Validate command line prediction parameter failed");
        return false;
      } else {
        LogDebug("Validate command line prediction parameter succeed");
      }
    } catch (std::exception& e) {
      LogError(e.what());
      return false;
    }
  }
  LogInfo("Validate command line prediction parameter succeed");
  return true;
}

void CmdLine::ParseTrainParam(int argc, char* argv[]) {
  std::string train_file = std::string(argv[1]);
  std::string model_file = std::string(argv[2]);

  if (!file_exists(train_file)) {
    throw std::invalid_argument("Invalid input param: train_file, because training file don't exist");
  }
  TrainParam* train_param = param_->GetTrainParam();
  if (train_param == nullptr) {
    LogError("train_param is nullptr");
    return;
  }
  train_param->train_file = train_file;
  train_param->model_file = model_file;

  int i = 3;
  while (i < argc) {
    std::string str = std::string(argv[i]);
    if (str == "-t") {
      if (i + 1 < argc) {
        train_param->task = std::stoi(argv[i + 1]);
        i++;
      }
    } else if (str == "-m") {
      if (i + 1 < argc) {
        train_param->model = std::stoi(argv[i + 1]);
        i++;
      }
    } else if (str == "-me") {
      if (i + 1 < argc) {
        train_param->metric = std::string(argv[i + 1]);
        i++;
      }
    } else if (str == "-v") {
      if (i + 1 < argc) {
        train_param->valid_file = std::string(argv[i + 1]);
        i++;
      }
    } else if (str == "-k") {
      if (i + 1 < argc) {
        train_param->n_factors = std::stoi(argv[i + 1]);
        i++;
      }
    } else if (str == "-e") {
      if (i + 1 < argc) {
        train_param->n_epoch = std::stoi(argv[i + 1]);
        i++;
      }
    } else if (str == "-lr") {
      if (i + 1 < argc) {
        train_param->learning_rate = std::stof(argv[i + 1]);
        i++;
      }
    } else if (str == "-reg") {
      if (i + 1 < argc) {
        std::string tmp = std::string(argv[i + 1]);
        if (tmp.find('|') != std::string::npos) {
          std::vector<float> regs = split_in_float(tmp, '|');
          if (regs.size() != 3) {
            throw std::invalid_argument("Invalid input param: -reg" + tmp);
          }
          train_param->reg_w0 = regs[0];
          train_param->reg_W = regs[1];
          train_param->reg_V = regs[2];
        } else {
          float reg = std::stof(argv[i + 1]);
          train_param->reg_w0 = reg;
          train_param->reg_W = reg;
          train_param->reg_V = reg;
        }
        i++;
      }
    } else if (str == "-mean") {
      if (i + 1 < argc) {
        train_param->init_mean = std::stof(argv[i + 1]);
        i++;
      }
    } else if (str == "-stddev") {
      if (i + 1 < argc) {
        train_param->init_stddev = std::stof(argv[i + 1]);
        i++;
      }
    } else if (str == "-nt") {
      if (i + 1 < argc) {
        train_param->n_thread = std::stoi(argv[i + 1]);
        i++;
      }
    } else if (str == "-seed") {
      if (i + 1 < argc) {
        train_param->seed = std::stol(argv[i + 1]);
        i++;
      }
    } else if (str == "--no-norm") {
      train_param->norm = false;
    } else if (str == "--quiet") {
      train_param->quiet = true;
    } else {
      throw std::invalid_argument("Invalid input param: " + str);
    }
    i++;
  }
}

void CmdLine::ParsePredictionParam(int argc, char* argv[]) {

  std::string test_file = argv[1];
  std::string model_file = argv[2];
  if (!file_exists(test_file)) {
    throw std::invalid_argument("Invalid input param: test_file, because test file don't exist");
  }
  if (!file_exists(model_file)) {
    throw std::invalid_argument("Invalid input param: model_file, because model file don't exist");
  }
  PredictionParam* prediction_param = param_->GetPredictionParam();
  if (prediction_param == nullptr) return;
  prediction_param->model_file = model_file;
  prediction_param->test_file = test_file;

  int i = 3;
  while (i < argc) {
    std::string str = std::string(argv[i]);
    if (str == "-o") {
      if (i + 1 < argc) {
        prediction_param->output_file = std::string(argv[i + 1]);
        i++;
      }
    } else if (str == "-nt") {
      if (i + 1 < argc) {
        prediction_param->n_thread = std::stoi(argv[i + 1]);
        i++;
      }
    } else if (str == "--no-norm ") {
      prediction_param->norm = false;
    } else {
      throw std::invalid_argument("Invalid input param: " + str);
    }
    i++;
  }
}

CmdLine::~CmdLine() {
  if (param_) {
    delete param_;
    param_ = nullptr;
  }
}


