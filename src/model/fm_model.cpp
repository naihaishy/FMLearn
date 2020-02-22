//
// Created by naihai on 2020/1/18.
//

#include "model/fm_model.h"

#include <ctime>
#include <random>

#include "common/utils.h"
#include "common/log.h"

FMModel::FMModel(int task,
                 int n_features,
                 int n_factors,
                 float mean,
                 float stddev) {
  this->task_ = task;
  this->n_features_ = n_features;
  this->n_factors_ = n_factors;
  this->InitWeights(mean, stddev);
}

/**
 * 从模型文件构建FMModel
 * @param model_file
 */
FMModel::FMModel(const std::string& model_file) {
  try {
    if (!this->Load(model_file)) {
      LogError("Construct FMModel from file " + model_file + " failed");
      throw std::runtime_error("Construct FMModel failed");
    }
  } catch (std::exception& e) {
    LogError(e.what());
  }
}

void FMModel::InitWeights(float mean, float stddev) {
  // 分配内存
  this->W_ = new float[n_features_];
  this->V_ = new float[this->n_features_ * this->n_factors_];

  // 值初始化
  this->w0_ = 0.0;
  for (int i = 0; i < n_features_; ++i) {
    this->W_[i] = 0.0;
  }
  std::default_random_engine generator{};
  std::uniform_real_distribution<float> distribution(0.0, 1.0);

  for (int i = 0; i < n_features_; ++i) {
    for (int j = 0; j < n_factors_; ++j) {
      V_[i * n_factors_ + j] = distribution(generator);
    }
  }

  LogDebug("FMModel InitWeights succeed");
}

void FMModel::Reset() {
  this->InitWeights(0.0, 0.1);
}

void FMModel::Free() {
  delete[] W_;
  delete[] V_;
  LogDebug("FMModel Free succeed");
}
/**
 * 将model序列化到文件中
 * @param filename
 */
void FMModel::Save(const std::string& filename) {

  std::ofstream ofs(filename);
  // 当前时间
  ofs << time(nullptr) << std::endl;
  // 当前版本
  ofs << std::to_string(VERSION) << std::endl;
  // task
  ofs << task_ << std::endl;
  ofs << n_features_ << std::endl;
  ofs << n_factors_ << std::endl;
  // weights
  ofs << "#w0" << std::endl;
  ofs << w0_ << std::endl;
  ofs << "#W" << std::endl;
  for (int i = 0; i < n_features_; ++i) {
    ofs << W_[i] << "\t";
  }
  ofs << std::endl;

  ofs << "#V" << std::endl;
  for (int i = 0; i < n_features_; ++i) {
    for (int f = 0; f < n_factors_; ++f) {
      ofs << V_[i * n_factors_ + f] << "\t";
    }
    ofs << std::endl;
  }
  ofs << std::endl;
  ofs << "#OK" << std::endl;
  ofs.close();
  LogInfo("FMModel save succeed , keep in " + filename);
}

/**
 * 从文件中加载模型
 * @param filename
 * @return
 */
bool FMModel::Load(const std::string& filename) {

  std::ifstream ifs(filename);
  if (!ifs.is_open())
    return false;

  std::string line;
  if (!std::getline(ifs, line)) return false;
  std::string time_stamps = line;

  if (!std::getline(ifs, line)) return false;
  std::string version = line;
  if (version != std::to_string(VERSION)) {
    LogWarn("Incompatible model version " + version +
        " with current version " + std::to_string(VERSION));
    throw std::runtime_error("Incompatible model version");
  }

  if (!std::getline(ifs, line)) return false;
  task_ = std::stoi(line);

  if (!std::getline(ifs, line)) return false;
  n_features_ = std::stoi(line);

  if (!std::getline(ifs, line)) return false;
  n_factors_ = std::stoi(line);

  // 参数矩阵
  W_ = new float[n_features_];
  V_ = new float[n_features_ * n_factors_];

  if (!std::getline(ifs, line)) return false; // #w0
  if (!std::getline(ifs, line)) return false; // w0
  w0_ = std::stof(line);

  if (!std::getline(ifs, line)) return false; // #W
  if (!std::getline(ifs, line)) return false; // W
  auto result_w0 = split_in_float(line, '\t');
  for (int i = 0; i < n_features_; ++i) {
    W_[i] = result_w0[i];
  }

  if (!std::getline(ifs, line)) return false; // #V
  for (int i = 0; i < n_features_; ++i) {
    if (!std::getline(ifs, line)) return false; // Vi
    auto result_Vi = split_in_float(line, '\t');
    for (int f = 0; f < n_factors_; ++f) {
      V_[i * n_factors_ + f] = result_Vi[f];
    }
  }

  std::getline(ifs, line);
  if (!std::getline(ifs, line)) return false;; // #OK
  if (line == "#OK") {
    LogInfo("Model is Ok");
  } else {
    LogWarn("Model is something wrong");
    return false;
  }
  return true;
}
