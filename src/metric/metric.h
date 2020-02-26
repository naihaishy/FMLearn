//
// Created by naihai on 2020/2/20.
// 定义了指标类

#ifndef FMLEARN_METRIC_METRIC_H_
#define FMLEARN_METRIC_METRIC_H_

#include <string>
#include <vector>
#include <cassert>
#include <cmath>

/**
 * Usage :
 * Metirc *metric = new AccMetric();
 */
class Metric {

 public:
  Metric() = default;;
  virtual ~Metric() = default;

  // 累计计算指标
  virtual void Calculate(std::vector<float>& pred,
                         std::vector<float>& label) = 0;

  virtual std::string GetType() = 0;

  virtual float GetValue() = 0;

 private:

};

/**
 * Accuracy 分类指标 仅支持二分类
 */
class ACCMetric : public Metric {
 public:

  ACCMetric() : total_example_(0), true_predict_(0) {}

  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {
    assert(pred.size() == label.size());
    int n = pred.size();
    total_example_ += n;
    for (int i = 0; i < n; ++i) {
      int a = pred[i] > 0 ? 1 : -1;
      int b = label[i] > 0 ? 1 : -1;
      if (a == b) true_predict_++;
    }
  }

  void Reset() {
    total_example_ = 0;
    true_predict_ = 0;
  }

  float GetValue() override {
    return (true_predict_ * 1.0) / total_example_;
  }

  std::string GetType() override {
    return "Accuracy";
  }

 private:
  int total_example_;
  int true_predict_;
};

/**
 *  Precision 分类指标 仅支持二分类
 */
class PrecMetric : public Metric {
 public:

  PrecMetric() : true_positive_(0), false_positive_(0) {}

  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {
    assert(pred.size() == label.size());
    int n = pred.size();

    for (int i = 0; i < n; ++i) {
      int a = pred[i] > 0 ? 1 : -1;
      int b = label[i] > 0 ? 1 : -1;
      if (a > 0 && b > 0) {
        true_positive_++;
      } else if (a > 0 && b < 0) {
        false_positive_++;
      }
    }
  }

  void Reset() {
    true_positive_ = 0;
    false_positive_ = 0;
  }

  float GetValue() override {
    return (true_positive_ * 1.0) / (true_positive_ + false_positive_);
  }

  std::string GetType() override {
    return "Precision";
  }

 private:
  int true_positive_;
  int false_positive_;
};

/**
 * Recall 分类指标 仅支持二分类
 */
class RecallMetric : public Metric {
 public:

  RecallMetric() : true_positive_(0), false_negative_(0) {}

  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {
    assert(pred.size() == label.size());
    int n = pred.size();

    for (int i = 0; i < n; ++i) {
      int a = pred[i] > 0 ? 1 : -1;
      int b = label[i] > 0 ? 1 : -1;
      if (a > 0 && b > 0) {
        true_positive_++;
      } else if (a < 0 && b > 0) {
        false_negative_++;
      }
    }
  }

  void Reset() {
    true_positive_ = 0;
    false_negative_ = 0;
  }

  float GetValue() override {
    return (true_positive_ * 1.0) / (true_positive_ + false_negative_);
  }

  std::string GetType() override {
    return "Recall";
  }

 private:
  int true_positive_;
  int false_negative_;
};

/**
 *  AUC 分类指标 仅支持二分类
 */
class AUCMetric : public Metric {
 public:
  std::string GetType() override {
    return "AUC";
  }
  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {
    assert(pred.size() == label.size());
  }

  float GetValue() override {
    return 0;
  }
};

/**
 * MSE 均方误差 回归
 */
class MSEMetric : public Metric {
 public:
  MSEMetric() : error_(0), total_example_(0) {};

  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {
    assert(pred.size() == label.size());
    int n = pred.size();
    total_example_ += n;
    for (int i = 0; i < n; ++i) {
      error_ += (pred[i] - label[i]) * (pred[i] - label[i]);
    }
  }

  void Reset() {
    error_ = 0;
    total_example_ = 0;
  }

  float GetValue() override {
    return error_ / total_example_;
  }

  std::string GetType() override {
    return "MSE";
  }

 protected:
  float error_;
  int total_example_;
};

/**
 * RMSE 均方根误差 回归
 */
class RMSEMetric : public MSEMetric {
 public:

  float GetValue() override {
    return sqrt(error_) / total_example_;
  }

  std::string GetType() override {
    return "RMSE";
  }
};

/**
 * MAE 平均绝对误差 回归
 */
class MAEMetric : public Metric {
 public:

  MAEMetric() : error_(0), total_example_(0) {};

  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {
    assert(pred.size() == label.size());
    int n = pred.size();
    total_example_ += n;
    for (int i = 0; i < n; ++i) {
      error_ += fabs(pred[i] - label[i]);
    }
  }

  void Reset() {
    error_ = 0;
    total_example_ = 0;
  }

  float GetValue() override {
    return error_ / total_example_;
  }

  std::string GetType() override {
    return "MAE";
  }

 private:
  float error_;
  int total_example_;
};


#endif //FMLEARN_METRIC_METRIC_H_
