//
// Created by naihai on 2020/1/18.
//

#ifndef FMLEARN_CORE_FM_PARAM_H_
#define FMLEARN_CORE_FM_PARAM_H_

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
               bool norm) :
      learning_rate(learning_rate),
      reg_w0(reg_w0),
      reg_W(reg_W),
      reg_V(reg_V),
      norm(norm) {};

  // training
  float learning_rate = 0.1;
  float reg_w0 = 0.1;
  float reg_W = 0.1;
  float reg_V = 0.1;
  bool norm = true;

  bool is_train = false;
  bool on_disk = false;
  bool quiet = false;
};

#endif //FMLEARN_CORE_FM_PARAM_H_
