//
// Created by naihai on 2020/1/23.
// 损失函数 目标函数类 针对数据集的操作

#ifndef FMLEARN_LOSS_LOSS_H_
#define FMLEARN_LOSS_LOSS_H_

#include <vector>

#include "model/fm_model.h"
#include "model/hyper_param.h"
#include "common/thread_pool.h"
#include "data/data.h"
#include "score/score.h"

/**
 * Usage :
 * Loss *loss = new Loss();
 * loss->Initialize(score);
 */
class Loss {

 public:
  Loss() = default;
  virtual ~Loss() = default;

  /**
   * 初始化
   * @param score
   */
  void Initialize(Score* score) {
    score_ = score;
  }

  /**
   * 重置 Calculate 与  CalGrad都会计算loss, 因此两个需要单独使用
   * Calculate一般用于测试数据
   * CalGrad一般用于训练时的loss
   * 使用前需要 Reset()
   */
  void Reset() {
    loss_sum_ = 0.0f;
    num_samples_ = 0;
  }

  /**
   * 根据预测值与真值计算损失 累计计算
   * @param preds 预测值
   * @param labels 真实标签
   */
  virtual void Calculate(std::vector<float>& preds,
                         std::vector<float>& labels) = 0;

  /**
   * 根据model对data进行预测
   * @param data 待预测的数据
   * @param model FMModel模型
   * @param preds 预测结果输出
   */
  virtual void Predict(const DMatrix* data,
                       FMModel& model,
                       std::vector<float>& preds);

  /**
   * 给定数据集 计算损失函数对所有样本的梯度并更新参数
   * @param data 训练数据
   * @param model FMModel模型
   */
  virtual void CalGrad(const DMatrix* data, FMModel* model) = 0;

  virtual std::string GetType() = 0;

  // 返回loss结果
  float GetValue() { return loss_sum_ / static_cast<float >(num_samples_); }

 protected:
  float loss_sum_ = 0.0f;
  int num_samples_ = 0;
  Score* score_;
  ThreadPool* pool_;
};

#endif //FMLEARN_LOSS_LOSS_H_
