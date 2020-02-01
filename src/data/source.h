//
// Created by naihai on 2020/1/30.
// 数据源 DataSource 针对数据源的操作
// 包含多个reader 每个reader可能类型不同


#ifndef FMLEARN_DATA_SOURCE_H_
#define FMLEARN_DATA_SOURCE_H_

#include "reader.h"
#include "data.h"
#include <vector>
#include <string>
#include <memory>

/**
 *
 */

class DataSource {
 public:
  /**
   * 从文件列表初始化DataSource
   * @param files
   */
  void Initialize(std::vector<std::string>& files);
  /**
   * 从目录初始化 DataSource
   * @param dir
   */
  void Initialize(const std::string& dir);
  /**
   *
   * @param reader
   */
  void AddRead(DataReader* reader);
  /**
   *
   * @return
   */
  std::vector<DMatrix*> Load();

 private:
  std::vector<DataReader*> readers_;
};

#endif //FMLEARN_DATA_SOURCE_H_
