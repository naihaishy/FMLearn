//
// Created by naihai on 2020/2/20.
//

#include "solver/solver.h"

#include "loss/squared_loss.h"
#include "loss/cross_entropy_loss.h"
#include "score/linear_score.h"
#include "score/fm_score.h"

#include "solver/trainer.h"
#include "solver/predictor.h"

void Solver::Initialize(HyperParam* param) {
  param_ = param;
  if (param_->is_train) {
    InitTrain();
  } else {
    InitPredict();
  }
  LogDebug("Solver Initialize done");
}

/**
 * 初始化训练参数
 * 准备 Trainer 需要的初始化参数
 */
void Solver::InitTrain() {
  TrainParam* train_param = param_->GetTrainParam();

  // 获取num_feature
  auto reader = new DataReader(train_param->train_file, true);
  reader->Initialize();
  auto data = new DMatrix();
  reader->Read(data);

  int num_feature = data->GetNumFeatures();

  // 初始化 score_
  if (train_param->model == LINER_MODEL) score_ = new LinearScore();
  else score_ = new FmScore();
  score_->Initialize(param_);

  // 初始化 loss_
  if (train_param->task == REGRESSION) loss_ = new SquaredLoss();
  else loss_ = new CrossEntropyLoss();
  loss_->Initialize(score_);


  // 初始化 model_
  if (train_param->model == LINER_MODEL) {
    model_ = nullptr;
  } else {
    model_ = new FMModel(train_param->task,
                         num_feature,
                         train_param->n_epoch,
                         train_param->init_mean,
                         train_param->init_stddev);
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
  } else if (train_param->metric == "rmse") {
    metric_ = new RMSEMetric();
  } else if (train_param->metric == "mae") {
    metric_ = new MAEMetric();
  } else {
    metric_ = nullptr;
  }

  // 初始化reader_list_
  reader_list_.clear();
  if (train_param->cross_validation) {
    //交叉验证 将文件分割为多个子文件
    std::vector<std::string> all_files;
    split_file_in_lines(train_param->train_file, train_param->num_folds, all_files);
    for (const auto& file_name:all_files) {
      reader_list_.emplace_back(new DataReader(file_name, true));
    }
  } else {
    reader_list_.emplace_back(new DataReader(train_param->train_file, true));
    if (!train_param->valid_file.empty()) {
      reader_list_.emplace_back(new DataReader(train_param->valid_file, true));
    }
  }

  LogDebug("Solver InitTrain done");
  std::string info;
  info.append("Solver Info: \n");
  info.append("task            : " + std::to_string(train_param->task) + "\n");
  info.append("model           : " + std::to_string(train_param->model) + "\n");
  info.append("train_file      : " + train_param->train_file + "\n");
  info.append("validation_file : " + train_param->valid_file + "\n");
  info.append("model_file      : " + train_param->model_file + "\n");
  info.append("loss type       : " + loss_->GetType() + "\n");
  info.append("score type      : " + score_->GetType() + "\n");
  LogInfo(info);
}

/**
 * 初始化预测参数
 * 准备 Predictor 需要的初始化参数
 */
void Solver::InitPredict() {
  PredictionParam* prediction_param = param_->GetPredictionParam();

  // 初始化 model_
  model_ = new FMModel(prediction_param->model_file);

  // 初始化 score_
  if (model_->GetModel() == LINER_MODEL) score_ = new LinearScore();
  else score_ = new FmScore();
  score_->Initialize(param_);

  // 初始化 loss_
  if (model_->GetTask() == REGRESSION) loss_ = new SquaredLoss();
  else loss_ = new CrossEntropyLoss();
  loss_->Initialize(score_);

  // 初始化reader_list_
  reader_list_.clear();
  reader_list_.emplace_back(new DataReader(prediction_param->test_file, false));

  LogDebug("Solver InitPredict done");
}

void Solver::Start() {
  if (param_->is_train) {
    LogDebug("Solver Start Train");
    StartTrain();
  } else {
    LogDebug("Solver Start Predict");
    StartPredict();
  }
}

void Solver::StartTrain() {
  TrainParam* train_param = param_->GetTrainParam();
  Trainer trainer;
  trainer.Initialize(reader_list_,
                     loss_,
                     model_,
                     metric_,
                     train_param->n_epoch,
                     train_param->early_stop,
                     train_param->stop_window,
                     train_param->quiet);

  if (train_param->cross_validation) trainer.CVTrain();
  else trainer.Train();

  // 保存模型
  if (!train_param->cross_validation && !train_param->model_file.empty()) {
    model_->Save(train_param->model_file);
  }
}

void Solver::StartPredict() {
  PredictionParam* prediction_param = param_->GetPredictionParam();
  Predictor predictor;
  predictor.Initialize(reader_list_.back(),
                       loss_,
                       model_,
                       prediction_param->output_file);
  predictor.Predict();
}

Solver::~Solver() {

  for (auto& reader : reader_list_) {
    delete reader;
    reader = nullptr;
  }
  std::vector<DataReader*>().swap(reader_list_);

  if (loss_ != nullptr) delete loss_;
  if (score_ != nullptr) delete score_;
  if (model_ != nullptr) delete model_;
  if (metric_ != nullptr) delete metric_;
  if (param_ != nullptr) delete param_;

  score_ = nullptr;
  loss_ = nullptr;
  model_ = nullptr;
  metric_ = nullptr;
  param_ = nullptr;
}


