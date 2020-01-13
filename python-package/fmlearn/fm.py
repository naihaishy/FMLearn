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
    def __init__(self, task, n_features, n_factors, lr, reg, init_mean=0.0, init_stddev=0.1):
        self.__handle = ctypes.c_void_p()  # 指向C++ FactorizationMachine对象的内存区域

        self.init_stddev = init_stddev
        self.init_mean = init_mean
        self.reg_w0 = reg[0]
        self.reg_W = reg[1]
        self.reg_V = reg[2]
        self.lr = lr
        self.n_factors = n_factors
        self.n_features = n_features
        self.task = task

        _check_call(_LIB.FMCreate(ctypes.byref(self.__handle),
                                  ctypes.c_int(self.task),
                                  ctypes.c_int(self.n_features),
                                  ctypes.c_int(self.n_factors),
                                  ctypes.c_float(self.lr),
                                  ctypes.c_float(self.reg_w0),
                                  ctypes.c_float(self.reg_W),
                                  ctypes.c_float(self.reg_V),
                                  ctypes.c_float(self.init_mean),
                                  ctypes.c_float(self.init_stddev)))

    def fit(self, X, y, n_iterations):
        data = DMatrix(data=X, label=y)
        _check_call(_LIB.FMFit(ctypes.byref(self.__handle),
                               ctypes.byref(data.handle),
                               ctypes.c_int(n_iterations)))
