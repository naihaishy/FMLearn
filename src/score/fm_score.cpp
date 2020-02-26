//
// Created by naihai on 2020/1/28.
//

#include "score/fm_score.h"
#include "model/hyper_param.h"

#include <algorithm>
#include <common/log.h>
#include <assert.h>

/**
 * 给定单个样本 计算FM 预测值
 * @param row 样本
 * @param model 模型
 * @param norm 归一化
 * @return
 */
float FmScore::Calculate(const SparseRow* row, FMModel& model, float norm) {
  float result = 0.0;

  float& w0 = model.GetBias();
  float*& W = model.GetW();
  float*& V = model.GetV();

  // bias
  result += w0;
  // linear term
  float sqrt_norm = sqrt(norm);
  for (auto& it : *row) {
    int i = it.feature_id;
    float xi = it.feature_val * sqrt_norm;
    result += W[i] * xi;
  }

  // interaction term
  float sum_inter = 0;
  int K = model.GetNumFactors();
  float inter1, inter2, d;
  for (int f = 0; f < K; ++f) {
    inter1 = 0.0;
    inter2 = 0.0;
    for (auto& it:*row) {
      int i = it.feature_id;
      float xi = it.feature_val * norm;
      float vif = V[i * K + f];
      d = vif * xi;
      inter1 += d;
      inter2 += d * d;
    }
    sum_inter += inter1 * inter1 - inter2;
  }
  sum_inter *= 0.5;
  result += sum_inter;

  return result;
}

/**
 * 给定单个样本 基于SGD计算梯度并更新model参数
 * @param row
 * @param model
 * @param norm
 * @param delta
 */
void FmScore::CalGrad(const SparseRow* row, FMModel& model, float norm, float delta) {

  TrainParam* train_param = hyper_param_->GetTrainParam();

  float lr = train_param->learning_rate;
  float reg_w0 = train_param->reg_w0;
  float reg_W = train_param->reg_W;
  float reg_V = train_param->reg_V;

  float& w0 = model.GetBias();
  float*& W = model.GetW();
  float*& V = model.GetV();

  // update bias
  w0 -= lr * (delta + 2 * reg_w0 * w0);
  int K = model.GetNumFactors();

  // update linear
  float sqrt_norm = sqrt(norm);
  for (auto& it:*row) {
    int i = it.feature_id;
    float xi = it.feature_val * sqrt_norm;
    float gradient_w = delta * xi;
    W[i] -= lr * (gradient_w + 2 * reg_W * W[i]);
  }

  // update intersection
  auto inter_sum = new float[K];
  for (int f = 0; f < K; ++f) {
    inter_sum[f] = 0.0;
    for (auto& it:*row) {
      int i = it.feature_id;
      float xi = it.feature_val * norm;
      float vif = V[i * K + f];
      inter_sum[f] += vif * xi;
    }
  }
  for (int f = 0; f < K; ++f) {
    for (auto& it : *row) {
      int i = it.feature_id;
      float xi = it.feature_val;
      float& vif = V[i * K + f];
      float gradient_v = delta * (xi * inter_sum[f] - vif * xi * xi);
      vif -= lr * (gradient_v + 2 * reg_V * vif);
    }
  }

  // 释放内存
  delete[] inter_sum;
}
FmScore::~FmScore() = default;
