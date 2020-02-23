//
// Created by naihai on 2020/2/19.
//

#include "solver/trainer.h"

#include "common/check.h"

/**
 * Trainer初始化
 * @param loss
 * @param model
 * @param metric 当metric为nullptr时使用loss作为判断标准
 * @param epoch 迭代次数
 * @param early_stop 是否早停
 * @param stop_window 早停窗口长度
 * @param quiet 为true时不对验证数据进行验证
 */
void Trainer::Initialize(std::vector<DataReader*>& reader_list,
                         Loss* loss,
                         FMModel* model,
                         Metric* metric,
                         int epoch,
                         bool early_stop,
                         int stop_window,
                         bool quiet) {
  CHECK_EQ(reader_list.empty(), false);
  CHECK_FALSE(loss == nullptr);
  CHECK_FALSE(model == nullptr);
  CHECK_GT(epoch, 0);

  reader_list_ = reader_list;
  loss_ = loss;
  model_ = model;
  metric_ = metric;
  epoch_ = epoch;
  early_stop_ = early_stop;
  stop_window_ = stop_window;
  quiet_ = quiet;
}

/**
 * 基本的训练
 */
void Trainer::Train() {
  std::vector<DataReader*> train_reader, valid_reader;
  train_reader.emplace_back(reader_list_[0]);

  if (reader_list_.size() == 2) {
    valid_reader.emplace_back(reader_list_[1]);
  }
  this->Train(train_reader, valid_reader);

}

/**
 * 交叉验证训练
 */
void Trainer::CVTrain() {
  int num_readers = reader_list_.size();
  for (int i = 0; i < num_readers; ++i) {
    // 构造训练数据与验证数据
    std::vector<DataReader*> train_reader, valid_reader;
    valid_reader.emplace_back(reader_list_[i]);
    for (int j = 0; j < num_readers && j != i; ++j) {
      train_reader.emplace_back(reader_list_[j]);
    }
    // 初始化model 重置参数
    // model_->Reset();
    this->Train(train_reader, valid_reader);
  }
}

/**
 *
 * @param train_reader 训练数据
 * @param valid_reader 验证数据
 */
void Trainer::Train(std::vector<DataReader*>& train_reader,
                    std::vector<DataReader*>& valid_reader) {

  int best_epoch = 0;
  int acc_stop_window = 0;

  float best_result = 0, prev_result = 0;
  bool less_is_better = true; // 标记是否值越小越好
  InitMetricValue(metric_, &best_result, &prev_result, &less_is_better);

  for (int i = 1; i <= epoch_; ++i) {
    // 计算梯度并更新model
    float train_loss = CalcGradient(train_reader);
    LogInfo("Epoch " + std::to_string(i) + " Train loss is " + std::to_string(train_loss));

    // 计算验证数据的性能指标
    if (!quiet_ && !valid_reader.empty()) {
      LossMetric valid_info = CalcMetric(valid_reader);

      // show evaluation metric info
      ShowTrainInfo(train_loss, valid_info, i);

      // Early-stopping
      if (early_stop_) {
        float current_result = metric_ == nullptr ? valid_info.loss_value : valid_info.metric_value;
        if ((less_is_better && current_result < best_result) ||
            (!less_is_better && current_result > best_result)) {
          best_result = current_result;
          best_epoch = i;
        }
        if ((less_is_better && current_result > prev_result) ||
            (!less_is_better && current_result < prev_result)) {
          acc_stop_window++;
        } else {
          acc_stop_window = 0;
        }
        if (acc_stop_window == stop_window_) { break; }
        prev_result = current_result;
      }
    }
  }

  if (!quiet_ && !valid_reader.empty()) {
    if (early_stop_ && best_epoch != epoch_) {
      std::string log_msg = "Early-stopping at epoch " + std::to_string(best_epoch);
      if (metric_ == nullptr) {
        log_msg += ", best loss is " + std::to_string(best_result);
      } else {
        log_msg += ", best " + metric_->GetType() + " is " + std::to_string(best_result);
      }
      LogInfo(log_msg);
    }
  }
  LogInfo("Train done");
}

float Trainer::CalcGradient(std::vector<DataReader*>& train_reader) {
  loss_->Reset();
  for (auto& reader : train_reader) {
    auto data = new DMatrix();
    reader->Initialize();
    reader->Read(data);
    LogDebug("ok");
    loss_->CalGrad(data, model_);
    LogDebug("loss_->CalGrad ok");
    // 释放内存
    //data->Free();
    // delete data;
  }
  return loss_->GetValue();
}

/**
 * 计算指标
 * @param valid_reader
 * @return LossMetric
 */
LossMetric Trainer::CalcMetric(std::vector<DataReader*>& valid_reader) {
  std::vector<float> preds;
  auto data = new DMatrix();
  for (auto& reader:valid_reader) {
    data->Free();
    reader->Initialize();
    reader->Read(data);
    loss_->Predict(data, *model_, preds);

    if (metric_ == nullptr) loss_->Calculate(preds, data->labels);
    else metric_->Calculate(preds, data->labels);
  }

  LossMetric info;
  info.loss_value = loss_->GetValue();
  if (metric_ != nullptr) info.metric_value = metric_->GetValue();

  // 释放内存
  data->Free();
  delete data;

  return info;
}

void Trainer::ShowTrainInfo(float train_loss, LossMetric& loss_metric, int epoch) {
  if (metric_ == nullptr) {
    LogInfo("Epoch : " + std::to_string(epoch) +
        ", Train Loss : " + std::to_string(train_loss) +
        ", Valid Loss : " + std::to_string(loss_metric.loss_value));
  } else {
    LogInfo("Epoch : " + std::to_string(epoch) +
        ", Train Loss : " + std::to_string(train_loss) +
        ", Metric Value : " + std::to_string(loss_metric.metric_value));
  }
}

void InitMetricValue(Metric* metric,
                     float* best_result,
                     float* prev_result,
                     bool* less_is_better) {
  if (metric == nullptr) {
    *best_result = FLOAT_MAX;
    *prev_result = FLOAT_MIN;
    *less_is_better = true;
  } else {
    std::string metric_type = metric->GetType();

    if (metric_type == "Accuracy" || metric_type == "Precision" ||
        metric_type == "Recall" || metric_type == "F1" || metric_type == "AUC") {
      // Classification
      *best_result = FLOAT_MIN;
      *prev_result = FLOAT_MAX;
      *less_is_better = false;
    } else if (metric_type == "MAE" || metric_type == "MAPE" || metric_type == "RMSD") {
      // regression
      *best_result = FLOAT_MAX;
      *prev_result = FLOAT_MIN;
      *less_is_better = true;
    }
  }
}



