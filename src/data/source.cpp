//
// Created by naihai on 2020/1/30.
//
#include "source.h"
#include <cassert>
#include <fstream>

/**
 * DataSource初始化 从文件列表初始化
 * @param files 数据源所在路径 所有文件集合
 */
void DataSource::Initialize(std::vector<std::string>& files) {
  for (const auto& file :files) {
    DataReader *reader = new DataReader(file, true);
    AddRead(reader);
  }
}

/**
 * TODO DataSource初始化 从目录初始化
 * @param dir 数据源所在目录
 * TODO 支持正则刷选文件
 */
void DataSource::Initialize(const std::string& dir) {

}

/**
 * 添加reader
 * @param reader
 */
void DataSource::AddRead(DataReader* reader) {
  assert(reader != nullptr);
  readers_.emplace_back(reader);
}

/**
 * 从所有reader中加载数据
 * @return std::vector<DMatrix*>
 */
std::vector<DMatrix*> DataSource::Load() {
  std::vector<DMatrix*> results;
  for (DataReader*& reader :readers_) {
    DMatrix* data = new DMatrix();
    reader->Initialize();
    reader->Read(data);
    results.emplace_back(data);
  }
  return std::move(results);
}

