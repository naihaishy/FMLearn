//
// Created by naihai on 2020/1/29.
//

#include <sstream>

#include "common/utils.h"

std::vector<std::string> split_in_string(const std::string& str, const char pattern) {
  std::vector<std::string> res;
  std::stringstream input(str);
  std::string temp;
  while (getline(input, temp, pattern)) {
    res.push_back(temp);
  }
  return res;
}

std::vector<float> split_in_float(const std::string& str, const char pattern) {
  std::vector<float> res;
  std::stringstream input(str);
  std::string temp;
  while (getline(input, temp, pattern)) {
    res.push_back(stof(temp));
  }
  return res;
}

bool file_exists(const std::string& file_path) {
  std::ifstream ifs(file_path);
  return ifs.is_open();
}





