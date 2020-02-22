//
// Created by naihai on 2020/1/13.
//

#ifndef FMLEARN_COMMON_COMMON_H_
#define FMLEARN_COMMON_COMMON_H_

#include <chrono>

// 预编译定义

#define REGRESSION 0
#define CLASSIFICATION 1
#define SQUARE_LOSS 0
#define CROSS_ENTROPY_LOSS 1

#define LINER_MODEL 0
#define FM_MODEL 1

#define VERSION 0.1

inline double GetTime() {
  return std::chrono::duration<double>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

#define FLOAT_MAX std::numeric_limits<float>::max()
#define FLOAT_MIN std::numeric_limits<float>::min()

#endif //FMLEARN_COMMON_COMMON_H_
