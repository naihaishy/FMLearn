//
// Created by naihai on 2020/1/22.
//

#ifndef FMLEARN_COMMON_UTILS_H_
#define FMLEARN_COMMON_UTILS_H_
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "log.h"

std::vector<std::string> split_in_string(const std::string& str, char pattern);

std::vector<float> split_in_float(const std::string& str, char pattern);

bool file_exists(const std::string &file_path);

template<typename T>
void SaveVectorToFile(const std::vector<T>& data, const std::string& file_name) {
  try{
    std::ofstream ofs(file_name);
    for (auto& ele :data) {
      ofs << ele << '\t';
    }
    ofs << std::endl;
    ofs.close();
  }catch (std::exception &e){
    Logging::warning("Predictions save failed, due to " + std::string(e.what()));
  }
}

#endif //FMLEARN_COMMON_UTILS_H_
