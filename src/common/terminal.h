//
// Created by naihai on 2020/2/19.
// 终端输出格式
// 参考 https://en.wikipedia.org/wiki/ANSI_escape_code
// 参考 https://misc.flogisoft.com/bash/tip_colors_and_formatting


#ifndef FMLEARN_COMMON_TERMINAL_H_
#define FMLEARN_COMMON_TERMINAL_H_

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

namespace Color {

// 转移序列格式码
enum Code {
  /********* Formatting Set ********/
  FS_BOLD = 1,
  FS_DIM = 2,
  FS_UNDER_LINE = 4,
  FS_BLINK = 5,
  FS_REVERSE = 7,
  FS_HIDDEN = 8,

  /********* Formatting Reset ********/
  FR_ALL = 0,
  FR_BOLD = 21,
  FR_DIM = 22,
  FR_UNDER_LINE = 24,
  FR_BLINK = 25,
  FR_REVERSE = 27,
  FR_HIDDEN = 28,

  /********* Color for foreground 3/4 bit ********/
  FG_BLACK = 30,
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 33,
  FG_BLUE = 34,
  FG_MAGENTA = 35,
  FG_CYAN = 36,
  FG_WHITE = 37,
  FG_DEFAULT = 39,

  /********* Color for background 3/4 bit ********/
  BG_BLACK = 40,
  BG_RED = 41,
  BG_GREEN = 42,
  BG_YELLOW = 43,
  BG_BLUE = 44,
  BG_MAGENTA = 45,
  BG_CYAN = 46,
  BG_WHITE = 47,
  BG_DEFAULT = 49,
};

class Modifier {
 public:
  Modifier(Code code) : code(code) {};
  friend std::ostream& operator<<(std::ostream& os, const Modifier& modifier) {
    return os << "\033[" << modifier.code << "m";
  }
  Code code;
};

}

inline void PrintDefault(const std::string& out, bool important) {
  Color::Modifier bold(Color::FS_BOLD);
  Color::Modifier reset(Color::FR_ALL);
  if (important) {
    std::cout << bold << out << reset << std::endl;
  } else {
    std::cout << out << reset << std::endl;
  }
}

inline void PrintDefault(const std::string& out) {
  PrintDefault(out, false);
}

inline void PrintInfo(const std::string& out, bool important) {
  Color::Modifier green(Color::FG_GREEN);
  Color::Modifier bold(Color::FS_BOLD);
  Color::Modifier reset(Color::FR_ALL);
  if (important) {
    std::cout << green << bold << out << reset << std::endl;
  } else {
    std::cout << green << out << reset << std::endl;
  }
}

inline void PrintInfo(const std::string& out) {
  PrintInfo(out, false);
}

inline void PrintWarning(const std::string& out, bool important) {
  Color::Modifier mag(Color::FG_MAGENTA);
  Color::Modifier bold(Color::FS_BOLD);
  Color::Modifier reset(Color::FR_ALL);
  if (important) {
    std::cout << mag << bold << out << reset << std::endl;
  } else {
    std::cout << mag << out << reset << std::endl;
  }
}

inline void PrintWarning(const std::string& out) {
  PrintWarning(out, false);
}

inline void PrintError(const std::string& out, bool important) {
  Color::Modifier red(Color::FG_RED);
  Color::Modifier bold(Color::FS_BOLD);
  Color::Modifier reset(Color::FR_ALL);
  if (important) {
    std::cout << red << bold << out << reset << std::endl;
  } else {
    std::cout << red << out << reset << std::endl;
  }
}

inline void PrintError(const std::string& out) {
  PrintError(out, false);
}

//------------------------------------------------------------------------------
// Example:
//
//  column ->  "Name", "ID", "Count", "Price"
//  width -> 10, 10, 10, 10
//
// Output:
//
//   Name       ID        Count   Price
//   Fruit      0x101       50     5.27
//   Juice      0x102       20     8.73
//   Meat       0x104       30    10.13
//------------------------------------------------------------------------------
template<typename T>
void PrintRow(const std::vector<T>& column, const std::vector<int>& width) {
  assert(column.size() == width.size());
  for (size_t i = 0; i < column.size(); ++i) {
    std::cout.width(width[i]);
    std::cout << column[i];
  }
  std::cout << "\n";
}

#endif //FMLEARN_COMMON_TERMINAL_H_
