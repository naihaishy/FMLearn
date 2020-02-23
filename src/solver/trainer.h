//
// Created by naihai on 2020/2/19.
// Trainer class

#ifndef FMLEARN_SOLVER_TRAINER_H_
#define FMLEARN_SOLVER_TRAINER_H_

#include <string>
#include <vector>

#include "common/log.h"
#include "loss/loss.h"
#include "score/score.h"
#include "data/reader.h"
#include "metric/metric.h"

struct LossMetric {
  float loss_value = 0;
  float metric_value = 0;
};

/**
 *
 * Usage :
 * Trainer trainer;
 * trainer.Initialize();
 * trainer.CVTrain(); // trainer.Train();
 *
 */
class Trainer {
 public:
  Trainer() = default;;
  ~Trainer() = default;;

  void Initialize(std::vector<DataReader*>& reader_list,
                  Loss* loss,
                  FMModel* model,
                  Metric* metric,
                  int epoch,
                  bool early_stop,
                  int stop_window,
                  bool quiet);

  void Train();
  void CVTrain();

 private:

  void Train(std::vector<DataReader*>& train_reader,
             std::vector<DataReader*>& valid_reader);

  /**
   * 计算梯度并更新model参数
   * @param train_reader 训练数据
   * @return train loss 训练loss
   */
  float CalcGradient(std::vector<DataReader*>& train_reader);

  /**
   * 计算model的性能指标
   * @param valid_reader 验证数据
   * @return LossMetric
   */
  LossMetric CalcMetric(std::vector<DataReader*>& valid_reader);

  /**
   * 显示训练过程信息
   * @param train_loss
   * @param loss_metric
   * @param epoch
   */
  void ShowTrainInfo(float train_loss, LossMetric& loss_metric, int epoch);

  // 显示交叉验证的结果
  void ShowAverageMetric();

  std::vector<DataReader*> reader_list_; // 既包括训练数据 也包括验证数据
  Loss* loss_{};
  FMModel* model_{};
  Metric* metric_{};
  int epoch_{};
  bool early_stop_{};
  int stop_window_{};
  bool quiet_{};
  std::vector<LossMetric> loss_metrics_;
};

void InitMetricValue(Metric* metric,
                     float* best_result,
                     float* prev_result,
                     bool* less_is_better);

#endif //FMLEARN_SOLVER_TRAINER_H_
