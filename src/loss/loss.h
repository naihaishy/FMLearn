//
// Created by naihai on 2020/1/23.
// 针对数据集的操作 计算loss 计算梯度并更新参数

#ifndef FMLEARN_LOSS_LOSS_H_
#define FMLEARN_LOSS_LOSS_H_

#include "src/data/data.h"
#include "src/core/fm_model.h"

#include <vector>
#include <src/score/score.h>

class Loss {

 public:
  Loss() = default;
  virtual ~Loss() = default;

  /**
   * 根据预测值与真值计算损失
   * @param preds 预测值
   * @param labels 真实值
   * @return loss
   */
  virtual float Calculate(std::vector<float>& preds,
                          std::vector<float>& labels) = 0;
  /**
   *  给定数据集 计算损失函数对所有样本的梯度并更新参数
   * @param data DMatrix
   * @param model FMModel
   * @param hyper_param  FMHyperParam
   * @param score
   * @return loss 该数据集下的损失
   */
  virtual float CalGrad(DMatrix* data, FMModel* model, FMHyperParam* hyper_param, Score *score) = 0;
  // 更新参数
  // virtual void UpdateWeights(FMModel* model) = 0;

  virtual std::string GetType() = 0;

 private:
  double loss_sum = 0.0;
  int data_samples = 0;
};

#endif //FMLEARN_LOSS_LOSS_H_
