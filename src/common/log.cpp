//
// Created by naihai on 2020/1/20.
//

#include "common/log.h"
#include "common/utils.h"
#include "common/terminal.h"

#include <algorithm>
#include <ctime>

// 设置默认的Logging级别
LoggingLevel Logging::log_level = INFO;
bool Logging::save_to_file_ = false;
std::ofstream Logging::debug_log_ofs_;
std::ofstream Logging::info_log_ofs_;
std::ofstream Logging::warn_log_ofs_;
std::ofstream Logging::error_log_ofs_;

/**
 * log输出
 * @param level_ 大于该level的消息将被输出
 * @param msg
 */
void Logging::log(LoggingLevel level_,
                  const std::string& msg,
                  const std::string& file,
                  int line,
                  const std::string& function) {
  time_t current;
  time(&current);
  struct tm* time_info = localtime(&current);
  char time_string[128];
  strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

  std::string log_message = std::string(time_string) + " " + file + " " +
      std::to_string(line) + " (" + function + ") " + msg;

  if (level_ >= log_level) {
    switch (level_) {
      case DEBUG:PrintDefault("[DEBUG] " + log_message);
        if (Logging::save_to_file_) Logging::debug_log_ofs_ << log_message << "\n" << std::flush;
        break;
      case INFO:PrintInfo("[INFO] " + log_message);
        if (Logging::save_to_file_) Logging::info_log_ofs_ << log_message << "\n" << std::flush;
        break;
      case WARNING:PrintWarning("[WARNING] " + log_message);
        if (Logging::save_to_file_) Logging::warn_log_ofs_ << log_message << "\n" << std::flush;
        break;
      case ERROR:PrintError("[ERROR] " + log_message);
        if (Logging::save_to_file_) Logging::error_log_ofs_ << log_message << "\n" << std::flush;
        break;
      case FATAL:Logging::debug_log_ofs_.close();
        Logging::info_log_ofs_.close();
        Logging::warn_log_ofs_.close();
        Logging::error_log_ofs_.close();
        abort();
    }
  }
}

/**
 * 设置level
 * @param level int 0 DEBUG 1 INFO 2 WARNING 3 ERROR 4 FATAL
 */
void Logging::SetLevel(int level) {
  switch (level) {
    case 0:Logging::log_level = LoggingLevel::DEBUG;
      break;
    case 1:Logging::log_level = LoggingLevel::INFO;
      break;
    case 2:Logging::log_level = LoggingLevel::WARNING;
      break;
    case 3:Logging::log_level = LoggingLevel::ERROR;
      break;
    case 4:Logging::log_level = LoggingLevel::FATAL;
      break;
    default:Logging::log_level = LoggingLevel::INFO;
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
}

/**
 * 设置Log文件的保存路径
 * @param log_dir 目录  每个级别单独保存 例如/tmp/logs/debug.log
 */

void SetLoggingDir(const std::string& log_dir) {
  if (log_dir.empty()) {
    Logging::save_to_file_ = false;
    throw std::invalid_argument("Log directory :" + log_dir + " is empty");
  }
  if (!file_exists(log_dir)) {
    Logging::save_to_file_ = false;
    throw std::invalid_argument("Log directory " + log_dir + " is not exist");
  }

  Logging::debug_log_ofs_.open(log_dir + "/debug.log", std::ofstream::out);
  Logging::info_log_ofs_.open(log_dir + "/info.log");
  Logging::warn_log_ofs_.open(log_dir + "/warn.log");
  Logging::error_log_ofs_.open(log_dir + "/error.log");

  if (Logging::debug_log_ofs_.is_open() == 0) {
    Logging::save_to_file_ = false;
    throw std::invalid_argument("can't create log file " + log_dir + "/debug.log");
  }
  if (Logging::info_log_ofs_.is_open() == 0) {
    Logging::save_to_file_ = false;
    throw std::invalid_argument("can't create log file " + log_dir + "/info.log");
  }
  if (Logging::warn_log_ofs_.is_open() == 0) {
    Logging::save_to_file_ = false;
    throw std::invalid_argument("can't create log file " + log_dir + "/warn.log");
  }
  if (Logging::error_log_ofs_.is_open() == 0) {
    Logging::save_to_file_ = false;
    throw std::invalid_argument("can't create log file " + log_dir + "/error.log");
  }
  Logging::save_to_file_ = true;
}