//
// Created by naihai on 2020/1/30.
//

#include <src/common/log.h>
#include "reader.h"
#include <vector>
#include <iostream>
#include <string>
#include <src/common/utils.h>

/**
 * Reader初始化
 * @return
 */
void DataReader::Initialize() {
  try {
    CheckFile();
  } catch (std::exception& e) {
    Logging::error(e.what());
    exit(0);
  }

  if (file_format_ == "csv")parser_ = new CSVParser();
  else if (file_format_ == "libsvm") parser_ = new LibSVMParser();
  else if (file_format_ == "libffm") parser_ = new LibFFMParser();
  parser_->Initialize(delimiter_, has_header_, has_label_);
  Logging::debug("Initialize is ok");
}

/**
 * 检查文件合法性
 * 判断文件是否存在header
 * 检测文件格式以及分隔符
 */
void DataReader::CheckFile() {
  std::ifstream ifs(file_path_);
  if (!ifs.is_open()) throw std::invalid_argument("Invalid file");

  std::string first_line;
  std::getline(ifs, first_line);
  ifs.close();

  // 判断是否存在header
  for (const char& c:first_line) {
    if ((c >= '0' && c <= '9') ||
        c == ',' || c == ' ' || c == '\t' ||
        c == ':' || c == '.' || c == '-')
      continue;
    else {
      has_header_ = true;
      break;
    }
  }
  if (has_header_) std::getline(ifs, first_line);

  if (first_line.empty())
    throw std::runtime_error("Invalid contents in file " + file_path_);

  delimiter_ = DataReader::ParseDelimiter(first_line);
  file_format_ = DataReader::ParseFileFormat(first_line, delimiter_);
  Logging::debug("CheckFile is ok");
}

/**
 * 从一行数据中个解析出分隔符
 * 解析原理： 选择出现次数最多的
 * @param line
 * @return delimiter \space \tab ,
 */
char DataReader::ParseDelimiter(const std::string& line) {
  char delimiter = ',';
  int table_count = 0;
  int space_cnt = 0;
  int comma_count = 0;

  for (char c: line) {
    if (c == ' ') space_cnt++;
    else if (c == '\t') table_count++;
    else if (c == ',') comma_count++;
  }

  if (table_count > space_cnt && table_count > comma_count) {
    delimiter = '\t';
  } else if (space_cnt > table_count && space_cnt > comma_count) {
    delimiter = ' ';
  } else if (comma_count > space_cnt && comma_count > table_count) {
    delimiter = ',';
  }
  return delimiter;
}
/**
 * 从一行数据中解析出文件格式
 *       label age is_student salary has_car
 * csv    1    12      0       1200    0
 * libsvm 1    1:12   3:1200
 * libffm 1    1:1:12 3:2:1200
 * @param line
 * @return file_format csv libsvm libffm
 */
std::string DataReader::ParseFileFormat(const std::string& line, char sep) {
  std::vector<std::string> arr = split_in_string(line, sep);
  if (arr.empty()) throw std::runtime_error("Invalid content or delitimer");

  int idx = 0; // 选择哪个数据项进行处理 因为可能存在label
  if (arr.size() == 1) idx = 0;// 因为没有label,故选择第一个
  else idx = 1; // 可能存在label,选择第二个

  int cnt = 0;
  for (char c: arr[idx]) if (c == ':') cnt++;
  if (cnt == 0) return "csv";
  else if (cnt == 1) return "libsvm";
  else if (cnt == 2) return "libffm";
  else throw std::runtime_error("Invalid file format");
}

/**
 * 读取数据 存入到DMatrix中
 * @param data
 */
void DataReader::Read(DMatrix* data) {
  std::ifstream infile(file_path_, std::ios::in);

  if (infile.is_open()) {
    std::string line;

    data->has_label = has_label_;
    if (has_header_) std::getline(infile, line);

    while (infile.good()) {
      std::getline(infile, line);
      if (line.empty()) break;
      // 解析行数据
      parser_->Parse(data, line);
    }
    infile.close();
    Logging::debug("DMatrix construct done");
  } else {
    Logging::error("file is closed before read data");
    throw std::runtime_error("input file is closed");
  }
}


