# -*- coding:utf-8 -*-
# @Time : 2020/1/12 15:56
# @Author : naihai

"""
Python 调用 C++ Api 底层实现的Factorization Machine
"""

import ctypes

from . import DMatrix
from .base import _LIB, _check_call


class FactorizationMachine(object):
    def __init__(self, task,
                 n_features,
                 n_factors,
                 lr, reg,
                 init_mean=0.0,
                 init_stddev=0.1,
                 norm=True, verbose=True):
        self.__handle = ctypes.c_void_p()  # 指向C++ FactorizationMachine对象的内存区域

        self.task = task
        self.n_features = n_features
        self.n_factors = n_factors
        assert (task == 0 or task == 1)

        self.lr = lr
        self.reg_w0 = reg[0]
        self.reg_W = reg[1]
        self.reg_V = reg[2]

        self.init_mean = init_mean
        self.init_stddev = init_stddev

        self.norm = norm
        self.verbose = verbose
        print(self.verbose)

        _check_call(_LIB.FMCreate(ctypes.byref(self.__handle),
                                  ctypes.c_int(self.task),
                                  ctypes.c_int(self.n_features),
                                  ctypes.c_int(self.n_factors),
                                  ctypes.c_float(self.lr),
                                  ctypes.c_float(self.reg_w0),
                                  ctypes.c_float(self.reg_W),
                                  ctypes.c_float(self.reg_V),
                                  ctypes.c_float(self.init_mean),
                                  ctypes.c_float(self.init_stddev),
                                  ctypes.c_bool(self.norm),
                                  ctypes.c_bool(self.verbose)))

    def fit(self, X, y, n_iterations):
        data = DMatrix(data=X, label=y)
        _check_call(_LIB.FMFit(ctypes.byref(self.__handle),
                               ctypes.byref(data.handle),
                               ctypes.c_int(n_iterations)))

    def predict(self, X):
        data = DMatrix(data=X)
        results = ctypes.POINTER(ctypes.c_float)()
        _check_call(_LIB.FMPredict(ctypes.byref(self.__handle),
                                   ctypes.byref(data.handle),
                                   ctypes.byref(results)))

        return [e for e in results]

    @staticmethod
    def set_log_level(level):
        level_ = 1
        if isinstance(level, int):
            level_ = level
        if isinstance(level, str):
            if level.lower() == "debug":
                level_ = 0
            elif level.lower() == "info":
                level_ = 1
            elif level.lower() == "warning":
                level_ = 2
            elif level.lower() == "error":
                level_ = 3
            elif level.lower() == "fatal":
                level_ = 4
            else:
                level_ = 1

        _check_call(_LIB.FMSetLogLevel(ctypes.c_int(level_)))
