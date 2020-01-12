//
// Created by naihai on 2020/1/12.
//
#include "c_api.h"
// #include "../data/data.h"
#include <iostream>
#include <bits/unique_ptr.h>

FM_DLL void hello() {
  std::cout << "Hello, World!" << std::endl;
}

FM_DLL int FMCreate(FM *out) {
  std::cout << "FMCreate " << std::endl;
  return 0;
}

FM_DLL int FMFit(FM *model, DataHandle *X, DataHandle *y, int *iterations) {
  std::cout << "FMFit " << std::endl;
  return 0;
}

FM_DLL int FMPredict(FM *model, DataHandle *X) {
  std::cout << "FMPredict " << std::endl;
  return 0;
}

// 创建DMatrix
FM_DLL int FMCreateDataFromMat(const float *data, int rows, int cols, const float *label, DataHandle *out) {
  // 使用智能指针管理DMatrix
  return 0;
}

FM_DLL int FMDataFree(DataHandle *out) {
  // 强制类型转换为DMatrix

  return 0;
}
