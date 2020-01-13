//
// Created by naihai on 2020/1/12.
// 定义了C API 错误处理 主要参考自xgboost和xlearn
/* This file defines the error handling for C API. */

#ifndef FMLEARN_C_API_ERROR_H_
#define FMLEARN_C_API_ERROR_H_

#include <string>
#include <stdexcept>
/**
 * 宏定义 监控所有的API函数
 */

/**
 * Every function starts with API_BEGIN();
 * and finishes with API_END() or API_END_HANDLE_ERROR
 * The finally clause contains procedure to cleanup states when an error happens.
 */
#define API_BEGIN() try{
#define API_END()  } catch(std::runtime_error &_except_) { return FMAPIHandleException(_except_); } return 0; // NOLINT(*)
#define API_END_HANDLE_ERROR(Finalize) } catch(std::runtime_error &_except_) { Finalize; return FMAPIHandleException(_except_); } return 0; // NOLINT(*)

// Get the last error message needed by C API
// FM_DLL const char * FMGetLastError(); // 需要暴露出去的接口函数

// Set the last error message needed by C API
void FMAPISetLastError(const char* msg);

inline int FMAPIHandleException(const std::runtime_error &e){
  FMAPISetLastError(e.what());
  return -1;
}

#endif //FMLEARN_C_API_ERROR_H_
