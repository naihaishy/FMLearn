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

#define VERSION 0.1

inline double GetTime() {
  return std::chrono::duration<double>(
      std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

#endif //FMLEARN_COMMON_COMMON_H_
