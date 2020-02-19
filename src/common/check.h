//
// Created by naihai on 2020/2/19.
// 定义一些检查函数

#ifndef FMLEARN_COMMON_CHECK_H_
#define FMLEARN_COMMON_CHECK_H_

#include "common/log.h"

#include <string>

#define REGISTER_CHECK_FUNCTION(name, op)                             \
template<typename X, typename Y>                                      \
  inline void CHECK##name(const X& x, const Y& y){                    \
    if(x op y){                                                       \
      LogDebug("CHECK" + std::string(#name) + " of " +                \
      std::to_string(x) + " and " + std::to_string(y) +               \
      " succeed : ");                                                 \
    }else{                                                            \
      LogError("CHECK" + std::string(#name) + " of " +                \
      std::to_string(x) + " and " + std::to_string(y) +               \
      " failed : ");                                                 \
    }                                                                 \
  }                                                                   \

REGISTER_CHECK_FUNCTION(_LT, <)
REGISTER_CHECK_FUNCTION(_GT, >)
REGISTER_CHECK_FUNCTION(_LE, <=)
REGISTER_CHECK_FUNCTION(_GE, >=)
REGISTER_CHECK_FUNCTION(_EQ, ==)
REGISTER_CHECK_FUNCTION(_NE, !=)

#endif //FMLEARN_COMMON_CHECK_H_
