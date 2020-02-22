//
// Created by naihai on 2020/2/20.
//

#include "solver/solver.h"
#include "solver/trainer.h"
#include "solver/predictor.h"
#include "loss/squared_loss.h"
#include "loss/cross_entropy_loss.h"
#include "score/linear_score.h"
#include "score/fm_score.h"

void Solver::Initialize(HyperParam* param) {
  hyper_param_ = param;
  if (hyper_param_->is_train) {
    InitTrain();
  } else {
    InitPredict();
  }
}

void Solver::SetTrain() {
  hyper_param_->is_train = true;
}

void Solver::SetPredict() {
  hyper_param_->is_train = false;
}

/**
 * 初始化训练参数
 * 准备 Trainer 需要的初始化参数
 */
void Solver::InitTrain() {
  TrainParam* train_param = hyper_param_->GetTrainParam();
  // 初始化 model_ loss_ score_
  if (train_param->model == LINER_MODEL) {
    model_ = nullptr;
    score_ = new LinearScore();
  } else {
    model_ = new FMModel();
    score_ = new FmScore();
  }

  if (train_param->task == REGRESSION) {
    loss_ = new SquaredLoss();
  } else {
    loss_ = new CrossEntropyLoss();
  }

  // 初始化 metric_
  metric_ = nullptr;
  if (train_param->metric == "acc") {
    metric_ = new ACCMetric();
  } else if (train_param->metric == "prec") {
    metric_ = new PrecMetric();
  } else if (train_param->metric == "recall") {
    metric_ = new RecallMetric();
  } else if (train_param->metric == "auc") {
    metric_ = new AUCMetric();
  } else if (train_param->metric == "mse") {
    metric_ = new MSEMetric();
  } else {
    metric_ = nullptr;
  }

  // 初始化reader_list_
  if (train_param->cross_validation) {
    reader_list_.clear();
    //交叉验证 将文件分割为多个子文件
    std::vector<std::string> all_files;
    split_file_in_lines(train_param->train_file, train_param->num_folds, all_files);
    for (const auto& file_name:all_files) {
      auto reader = new DataReader(file_name, true);
      reader_list_.emplace_back(reader);
    }
  } else {
    auto train_reader = new DataReader(train_param->train_file, true);
    auto valid_reader = new DataReader(train_param->valid_file, true);
    reader_list_.emplace_back(train_reader);
    reader_list_.emplace_back(valid_reader);
  }

  //

}

/**
 * 初始化预测参数
 * 准备 Predictor 需要的初始化参数
 */
void Solver::InitPredict() {
  PredictionParam* prediction_param = hyper_param_->GetPredictionParam();

  // 初始化 model_ loss_ score_
  if (prediction_param->model == LINER_MODEL) {
    model_ = nullptr;
  } else {
    model_ = new FMModel(prediction_param->model_file);
  }

  if (prediction_param->task == REGRESSION) {
    loss_ = new SquaredLoss();
  } else {
    loss_ = new CrossEntropyLoss();
  }

  // 初始化reader_list_
  auto reader = new DataReader(prediction_param->test_file, false);
  reader_list_.clear();
  reader_list_.emplace_back(reader);
}

void Solver::Start() {
  if (hyper_param_->is_train) {
    StartTrain();
  } else {
    StartPredict();
  }
}

void Solver::StartTrain() {
  TrainParam* train_param = hyper_param_->GetTrainParam();
  Trainer trainer;
  trainer.Initialize(reader_list_,
                     loss_,
                     model_,
                     metric_,
                     train_param->n_epoch,
                     train_param->early_stop,
                     train_param->stop_window,
                     train_param->quiet);
  trainer.Train();
}

void Solver::StartPredict() {
  PredictionParam* prediction_param = hyper_param_->GetPredictionParam();
  Predictor predictor;
  predictor.Initialize(reader_list_.back(),
                       loss_,
                       model_,
                       prediction_param->output_file);
  predictor.Predict();
}


