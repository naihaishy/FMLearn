//
// Created by naihai on 2020/1/12.
//

#ifndef FMLEARN__C_API_H_
#define FMLEARN__C_API_H_


#ifdef __cplusplus
#define FM_EXTERN_C extern "C"
#include <cstdio>
#include <cstdint>
#else
#define FM_EXTERN_C
#include "stdio.h"
#include "stdint.h"
#endif // __cplusplus

#if defined(_MSC_VER) || defined(_WIN32)
#define FM_DLL FM_EXTERN_C __declspec(dllexport)
#else
#define FM_DLL FM_EXTERN_C
#endif // _WIN32

FM_DLL void hello();

/* Handle to FMLearn */
typedef void *FM;
typedef void *DataHandle;

FM_DLL int FMCreate(FM *out);
FM_DLL int FMFit(FM *model, DataHandle *X, DataHandle *y, int *iterations);
FM_DLL int FMPredict(FM *model, DataHandle *X);

// Handle data matrix for FMLearn
FM_DLL int FMCreateDataFromMat(const float *data, int rows, int cols, const float *label, DataHandle *out);
FM_DLL int FMDataFree(DataHandle *out);

// Handle error
FM_DLL const char * FMGetLastError();

class FactorizationMachine {
 public:
  // Constructor and Destructor
  FactorizationMachine() {};
  ~FactorizationMachine() {};
  FactorizationMachine(const FactorizationMachine &other) = delete;
  void operator=(const FactorizationMachine &) = delete;
};



#endif //FM__C_API_H_
