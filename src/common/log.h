//
// Created by naihai on 2020/1/20.
//

#ifndef FMLEARN_COMMON_LOG_H_
#define FMLEARN_COMMON_LOG_H_

#include <string>
#include <iostream>
#include <fstream>

// Logging Level
enum LoggingLevel {
  DEBUG = 0,
  INFO = 1,
  WARNING = 2,
  ERROR = 3,
  FATAL = 4
};

class Logging {
 public:
  static LoggingLevel log_level;

  static void SetLevel(int level);
  static void SetLevel(const std::string& level);
  friend void SetLoggingDir(const std::string& log_dir);

  static void log(LoggingLevel level,
                  const std::string& msg,
                  const std::string& file,
                  int line,
                  const std::string& function);

 private:
  static std::ofstream debug_log_ofs_;
  static std::ofstream info_log_ofs_;
  static std::ofstream warn_log_ofs_;
  static std::ofstream error_log_ofs_;

  static bool save_to_file_; // 是否保存到文件中
  // static std::string log_dir_; //log日志保存目录
};

void SetLoggingDir(const std::string& log_dir);

#if defined(_MSC_VER) || defined(_WIN32)
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define LogDebug(msg) Logging::log(DEBUG, msg, __FILENAME__, __LINE__, __FUNCTION__)
#define LogInfo(msg) Logging::log(INFO, msg, __FILENAME__, __LINE__, __FUNCTION__)
#define LogWarn(msg) Logging::log(WARNING, msg, __FILENAME__, __LINE__, __FUNCTION__)
#define LogError(msg) Logging::log(ERROR, msg, __FILENAME__, __LINE__, __FUNCTION__)
#define LogFatal(msg) Logging::log(FATAL, msg, __FILENAME__, __LINE__, __FUNCTION__)

#endif //FMLEARN_COMMON_LOG_H_
