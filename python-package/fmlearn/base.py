# -*- coding:utf-8 -*-
# @Time : 2020/1/12 20:43
# @Author : naihai
import ctypes


def load_lib():
    return ctypes.cdll.LoadLibrary("E:\CLion\Projects\FMLearn\cmake-build-debug\libFMLearn.dll")


_LIB = load_lib()


class FMError(Exception):
    pass


def _check_call(ret):
    """
    检查 C API 返回值 并处理C API异常
    :param ret: return value from API calls
    :return:
    """
    if ret != 0:
        msg = _LIB.FMGetLastError()
        msg = msg.decode('utf-8')  # convert c string back to python string
        print(msg)
        raise FMError(msg)
