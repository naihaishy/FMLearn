//
// Created by naihai on 2020/1/30.
// Data Reader 操作文件 text模式 针对文件的操作
// 一个reader实例往往对应一个文件/句柄
// 内容只能是数值型（可以有header)

#ifndef FMLEARN_DATA_READER_H_
#define FMLEARN_DATA_READER_H_

#include "parser.h"
#include "data.h"
#include <iostream>
#include <string>

/**
 * Usage:
 * DataReader *reader = new DataReader("a.txt", true);
 * reader.Initialize(); // invoke before Read()
 * DMatrix *data = new DMatrix();
 * reader.Read(data);
 */
class DataReader {
 public:
  DataReader(const std::string& file_path, bool has_label) :
      file_path_(file_path),
      has_label_(has_label) {};

  void Initialize();
  void Read(DMatrix* data);

 private:
  void CheckFile();
  static char ParseDelimiter(const std::string& line);
  static std::string ParseFileFormat(const std::string& line, char sep);

  std::string file_path_;
  std::string file_format_; // 文件格式 csv/libsvm/libffm
  char delimiter_; // 数据项分隔符 \t , space
  bool has_header_ = false;
  bool has_label_ = false; // 如果有label,一定要放在头部 即第一列
  Parser* parser_; // 解析每行内容
};

#endif //FMLEARN_DATA_READER_H_
