//
// Created by naihai on 2020/1/13.
//

#ifndef FMLEARN_COMMON_COMMON_H_
#define FMLEARN_COMMON_COMMON_H_

// 预编译定义
#define USING_LOGGING

#ifdef USING_LOGGING
#define LOG_INFO(msg) std::cout << msg << std::endl;
#else
#define LOG_INFO(msg)
#endif // USING_LOGGING


#endif //FMLEARN_COMMON_COMMON_H_
