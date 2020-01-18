//
// Created by naihai on 2020/1/18.
//

#ifndef FMLEARN_CORE_FM_PARAM_H_
#define FMLEARN_CORE_FM_PARAM_H_

/**
 * FM 超参数
 */
struct FMHyperParam {
  bool is_train = false;
  bool on_disk = false;
  bool quiet = false;

  // training
  float learning_rate = 0.1;
  float reg_w0 = 0.1;
  float reg_W = 0.1;
  float reg_V = 0.1;
  bool norm = true;
};

#endif //FMLEARN_CORE_FM_PARAM_H_
