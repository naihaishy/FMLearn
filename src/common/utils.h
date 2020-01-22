//
// Created by naihai on 2020/1/22.
//

#ifndef FMLEARN_COMMON_UTILS_H_
#define FMLEARN_COMMON_UTILS_H_
#include <vector>
#include <string>
#include <sstream>

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

#endif //FMLEARN_SRC_COMMON_UTILS_H_
