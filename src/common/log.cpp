//
// Created by naihai on 2020/1/20.
//

#include "common/log.h"

#include <algorithm>

// 设置默认的Logging级别
LoggingLevel Logging::log_level = INFO;

/**
 * log输出
 * @param level_ 大于该level的消息将被输出
 * @param msg
 */
void Logging::log(LoggingLevel level_, const std::string& msg) {
  if (level_ >= log_level) {
    switch (level_) {
      case DEBUG: std::cout << "[DEBUG] ";
        break;
      case INFO:std::cout << "[INFO] ";
        break;
      case WARNING:std::cout << "[WARNING] ";
        break;
      case ERROR:std::cout << "[ERROR] ";
        break;
      case FATAL:std::cout << "[FATAL] ";
        break;
    }
    std::cout << msg << std::endl;
  }
}

/**
 * 设置level
 * @param level int 0 DEBUG 1 INFO 2 WARNING 3 ERROR 4 FATAL
 */
void Logging::SetLevel(int level) {
  switch (level) {
    case 0:
      Logging::log_level = LoggingLevel::DEBUG;
      break;
    case 1:
      Logging::log_level = LoggingLevel::INFO;
      break;
    case 2:
      Logging::log_level = LoggingLevel::WARNING;
      break;
    case 3:
      Logging::log_level = LoggingLevel::ERROR;
      break;
    case 4:
      Logging::log_level = LoggingLevel::FATAL;
      break;
    default:
      Logging::log_level = LoggingLevel::INFO;
      break;
  }
}

/**
 * 设置level
 * @param level std::string
 */
void Logging::SetLevel(const std::string& level) {
  std::string level_;
  std::transform(level.begin(), level.end(), level_.begin(), ::toupper);
  if (level_ == "DEBUG") {
    Logging::log_level = LoggingLevel::DEBUG;
  } else if (level_ == "INFO") {
    Logging::log_level = LoggingLevel::INFO;
  } else if (level_ == "WARNING") {
    Logging::log_level = LoggingLevel::WARNING;
  } else if (level_ == "ERROR") {
    Logging::log_level = LoggingLevel::ERROR;
  } else if (level_ == "FATAL") {
    Logging::log_level = LoggingLevel::FATAL;
  } else {
    Logging::log_level = LoggingLevel::INFO;
  }
};

std::string LogFileLineFunction(const std::string& file,
                                int line,
                                const std::string& function) {
  return " [File] " + file + " [Line] " + std::to_string(line) + " [Function] " + function;
}