//
// Created by naihai on 2020/1/22.
//

#ifndef FMLEARN_COMMON_UTILS_H_
#define FMLEARN_COMMON_UTILS_H_
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

std::vector<std::string> split_in_string(const std::string& str, char pattern);

std::vector<float> split_in_float(const std::string& str, char pattern);

bool file_exists(const std::string &file_path);

#endif //FMLEARN_SRC_COMMON_UTILS_H_
