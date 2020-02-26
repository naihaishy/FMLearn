//
// Created by naihai on 2020/1/12.
//

#include "c_api/c_api.h"

#include <iostream>
#include <memory>

#include "common/log.h"
#include "data/data.h"

FM_DLL void hello() {
  std::cout << "Hello, World!" << std::endl;
}

/**
 * 创建DMatrix
 * @param data pointer to the data space
 * @param rows number of data samples
 * @param cols number of data features
 * @param label pointer to the label space
 * @param out the created data matrix
 */
FM_DLL int FMMatrixCreateFromMat(const float* data, int rows, int cols, const float* label, DataHandle* out) {
  API_BEGIN()
    // 使用智能指针管理DMatrix
    std::unique_ptr<DMatrix> matrix(new DMatrix(data, label, rows, cols));
    *out = matrix.release();
    LogDebug("data matrix created succeed");
  API_END()
}

FM_DLL int FMMatrixCreateFromFile(const std::string& file_name,
                                  bool has_label,
                                  DataHandle* out) {
  API_BEGIN()
    // 使用智能指针管理DMatrix
    std::unique_ptr<DMatrix> matrix(new DMatrix(file_name, has_label));
    *out = matrix.release();
    LogDebug("data matrix created succeed");
  API_END()
}

/**
 * 释放DMatrix
 * @param out the created data matrix
 */
FM_DLL int FMMatrixFree(DataHandle* out) {
  API_BEGIN()
    // 强制将out类型转换为DMatrix
    auto matrix = reinterpret_cast<DMatrix*>(*out);
    // delete matrix;
    LogDebug("data matrix free succeed");
  API_END()
}

/**
 * 创建FactorizationMachine实例
 *  @param out the created FactorizationMachine instance
 */
FM_DLL int FMCreate(FM* out, int task, int n_features, int n_factors,
                    float lr, float reg_w0, float reg_W, float reg_V,
                    float mean, float stddev,
                    bool norm, bool verbose) {
  API_BEGIN()

    LogDebug("FMCreate succeed");
  API_END()
}

/**
 * @param out 模型指针
 * @param X
 * @param y
 * @param iterations
 */
FM_DLL int FMFit(FM* out, DataHandle* data, int iterations) {
  API_BEGIN()
    // 强制将out类型转换为FactorizationMachine

    LogDebug("FMFit succeed");
  API_END()
}

FM_DLL int FMPredict(FM* out, DataHandle* data, DataHandle* out_result) {
  API_BEGIN()
    // 模型类型转换

    LogDebug("FMPredict succeed");
  API_END()
}

/**
 * 设置Log级别
 * @param level 0 DEBUG 1 INFO 2 WARNING 3 ERROR 4 FATAL
 * @return
 */
FM_DLL int FMSetLogLevel(int level) {
  API_BEGIN()
    Logging::SetLevel(level);
  API_END()
}

