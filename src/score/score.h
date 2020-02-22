//
// Created by naihai on 2020/1/28.
// 针对单个样本的操作 计算预测值 计算梯度更新参数

#ifndef FMLEARN_SCORE_SCORE_H_
#define FMLEARN_SCORE_SCORE_H_

#include "model/fm_model.h"
#include "model/hyper_param.h"
#include "data/data.h"

class Score {
 public:
  Score() = default;
  virtual ~Score() = default;

  void Initialize(HyperParam* hyper_param);

  /**
   * 给定单个样本 计算预测值
   * @param row 样本
   * @param model 当前模型
   * @param norm 归一化因子
   * @return 预测值 predicted value
   */
  virtual float Calculate(SparseRow* row, FMModel& model, float norm) = 0;

  /**
   * 给定单个样本 计算梯度并更新model参数 SGD
   * @param row 样本
   * @param model 当前模型
   * @param norm 归一化因子
   * @param delta
   */
  virtual void CalGrad(SparseRow* row, FMModel& model, float norm, float delta) = 0;

  virtual std::string GetType() { return type_; }

 protected:
  std::string type_ = "Score";
  HyperParam *hyper_param_;
};

#endif //FMLEARN_SCORE_SCORE_H_
