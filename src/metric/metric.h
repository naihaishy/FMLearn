//
// Created by naihai on 2020/2/20.
// 定义了指标类

#ifndef FMLEARN_METRIC_METRIC_H_
#define FMLEARN_METRIC_METRIC_H_
#include <string>



class Metric {

 public:
  Metric();
  ~Metric();

  // 累计计算指标
  virtual void Calculate(std::vector<float>& pred, std::vector<float>& label) = 0;
  virtual std::string GetType() = 0;
  virtual float GetValue() = 0;

 private:

};

/**
 *
 */
class ACCMetric : public Metric {
 public:
  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {

  }
  std::string GetType() override {
    return "Accuracy";
  }
  float GetValue() override {
    return 0;
  }

};

/**
 *
 */
class PrecMetric : public Metric {
 public:
  std::string GetType() override {
    return "Precision";
  }
  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {

  }
  float GetValue() override {
    return 0;
  }
};

/**
 *
 */
class RecallMetric : public Metric {
 public:
  std::string GetType() override {
    return "Recall";
  }
  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {

  }
  float GetValue() override {
    return 0;
  }
};

/**
 *
 */
class AUCMetric : public Metric {
 public:
  std::string GetType() override {
    return "AUC";
  }
  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {

  }
  float GetValue() override {
    return 0;
  }
};

/**
 *
 */
class MSEMetric : public Metric {
 public:
  std::string GetType() override {
    return "MSE";
  }
  void Calculate(std::vector<float>& pred, std::vector<float>& label) override {

  }
  float GetValue() override {
    return 0;
  }
};

#endif //FMLEARN_METRIC_METRIC_H_
