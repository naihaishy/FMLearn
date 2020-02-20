//
// Created by naihai on 2020/2/19.
// 定义一些检查函数

#ifndef FMLEARN_COMMON_CHECK_H_
#define FMLEARN_COMMON_CHECK_H_

#include "common/log.h"

#include <string>

#define REGISTER_CHECK_FUNCTION(name, op)                             \
template<typename X, typename Y>                                      \
  inline void CHECK_BINARY##name(const X& x, const Y& y){                    \
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

#define CHECK_LT(x, y) CHECK_BINARY_LT(x, y)
#define CHECK_GT(x, y) CHECK_BINARY_GT(x, y)
#define CHECK_LE(x, y) CHECK_BINARY_LE(x, y)
#define CHECK_GE(x, y) CHECK_BINARY_GE(x, y)
#define CHECK_EQ(x, y) CHECK_BINARY_EQ(x, y)
#define CHECK_NE(x, y) CHECK_BINARY_NE(x, y)
#define CHECK_TRUE(x) CHECK_EQ(x, true)
#define CHECK_FALSE(x) CHECK_EQ(x, false)

#endif //FMLEARN_COMMON_CHECK_H_
