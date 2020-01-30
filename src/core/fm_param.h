//
// Created by naihai on 2020/1/18.
//

#ifndef FMLEARN_CORE_FM_PARAM_H_
#define FMLEARN_CORE_FM_PARAM_H_
#include <iostream>
#include <string>

/**
 * FM 超参数
 */
class FMHyperParam {

 public:
  FMHyperParam() = default;
  FMHyperParam(float learning_rate,
               float reg_w0,
               float reg_W,
               float reg_V,
               bool norm,
               bool verbose) :
      learning_rate(learning_rate),
      reg_w0(reg_w0),
      reg_W(reg_W),
      reg_V(reg_V),
      norm(norm),
      verbose(verbose){};

  // training
  float learning_rate = 0.1;
  float reg_w0 = 0.1;
  float reg_W = 0.1;
  float reg_V = 0.1;
  bool norm = true;

  bool is_train = false;
  bool on_disk = false;
  bool verbose = false;

  std::string to_string() {
    std::string result;
    result.reserve(1024);
    result.append("FMHyperParam: \n");
    result.append("learning_rate : " + std::to_string(learning_rate) + "\n");
    result.append("reg_w0        : " + std::to_string(reg_w0) + "\n");
    result.append("reg_W         : " + std::to_string(reg_W) + "\n");
    result.append("reg_V         : " + std::to_string(reg_V) + "\n");
    result.append("norm          : " + std::to_string(norm) + "\n");
    result.append("is_train      : " + std::to_string(is_train) + "\n");
    result.append("on_disk       : " + std::to_string(on_disk) + "\n");
    result.append("verbose       : " + std::to_string(verbose) + "\n");
    return result;
  }
};

#endif //FMLEARN_CORE_FM_PARAM_H_
