//
// Created by naihai on 2020/1/20.
//

#ifndef FMLEARN_COMMON_LOG_H_
#define FMLEARN_COMMON_LOG_H_

#include <string>
#include <iostream>

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
  static void debug(const std::string& msg) {
    log(DEBUG, msg);
  }
  static void info(const std::string& msg) {
    log(INFO, msg);
  }
  static void warning(const std::string& msg) {
    log(WARNING, msg);
  }
  static void error(const std::string& msg) {
    log(ERROR, msg);
  }
  static void fatal(const std::string& msg) {
    log(FATAL, msg);
  }

  static void SetLevel(int level);
  static void SetLevel(const std::string &level);

 private:
  static void log(LoggingLevel level, const std::string& msg);
};

#endif //FMLEARN_COMMON_LOG_H_
