//
// Created by naihai on 2020/1/18.
//

#ifndef FMLEARN_COMMON_MATH_H_
#define FMLEARN_COMMON_MATH_H_

#include <cmath>
inline float sigmoid(float x) {
  return 1.0f / (1.0f + expf(-x));
}


#endif //FMLEARN_COMMON_MATH_H_
