//
// Created by naihai on 2020/1/12.
//

#ifndef FMLEARN_C_API_H_
#define FMLEARN_C_API_H_

#include "../data/data.h"
#include "../core/model.h"
#include "../common/common.h"
#include "c_api_error.h"

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
typedef void* FM;
typedef void* DataHandle;

// Handle data matrix for FMLearn
FM_DLL int FMMatrixCreateFromMat(const float* data, int rows, int cols, const float* label, DataHandle* out);
FM_DLL int FMMatrixFree(DataHandle* out);

// Handle FactorizationMachine
FM_DLL int FMCreate(FM* out, int task, int n_features, int n_factors,
                    float lr, float reg_w0, float reg_W, float reg_V,
                    float mean, float stddev);
FM_DLL int FMFit(FM* out, DataHandle* data, int iterations);
FM_DLL int FMPredict(FM* out, DataHandle* data, DataHandle* results);

// Handle error
FM_DLL const char* FMGetLastError();

#endif //FMLEARN_C_API_H_
