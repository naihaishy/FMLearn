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
  std::ifstream ifs(file_path, std::ifstream::in);
  if (ifs.is_open()) {
    ifs.close();
    return true;
  } else {
    return false;
  }
}

void split_file_in_size(const std::string& file_path, int num) {
  // 获取文件长度
  std::ifstream ifs(file_path, std::ifstream::binary);
  if (!ifs.is_open()) {
    LogError("Split file " + file_path + " not exist");
    return;
  }
  ifs.seekg(0, std::ifstream::end);
  long long file_size = ifs.tellg();
  LogInfo("Line Num" + std::to_string(file_size));

  ifs.seekg(0);

  // 切分
  long long average_file_size = file_size / num + 1;
  for (int i = 0; i < num; ++i) {
    char* buffer = new char[average_file_size];
    std::string out_file = file_path + "_" + std::to_string(i);
    ifs.read(buffer, average_file_size);
    std::ofstream ofs(out_file);
    ofs.write(buffer, average_file_size);
    ofs.flush();
    ofs.close();
    delete[] buffer;

    ifs.seekg((i + 1) * average_file_size);
  }

  ifs.close();
}

void split_file_in_lines(const std::string& file_path,
                         int num,
                         std::vector<std::string>& out_files) {
  std::ifstream ifs(file_path);
  if (!ifs.is_open()) {
    LogError("Split file " + file_path + " not exist");
    return;
  }
  long long file_lines = 0;
  std::string line;
  while (std::getline(ifs, line)) {
    file_lines++;
  }
  long long average_file_line = file_lines / num + 1;
  ifs.close();
  ifs.open(file_path);

  for (int i = 0; i < num; ++i) {
    std::string out_file = file_path + "_" + std::to_string(i);
    std::ofstream ofs(out_file, std::ofstream::out);
    for (int j = 0; j < average_file_line; ++j) {
      std::string text_line;
      ifs >> text_line;
      if (!text_line.empty()) ofs << text_line << "\n";
    }
    ofs.flush();
    ofs.close();
    out_files.push_back(out_file);
  }
  ifs.close();
}





