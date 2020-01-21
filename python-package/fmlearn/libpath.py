# -*- coding:utf-8 -*-
# @Time : 2020/1/16 23:58
# @Author : naihai
"""Find the path to fmlearn dynamic library files."""

import os
import platform
import sys


class FMLearnLibraryNotFound(Exception):
    """Error thrown by when lib is not found"""
    pass


def find_lib_path():
    curr_path = os.path.dirname(os.path.abspath(os.path.expanduser(__file__)))

    # make pythonpack hack: copy this directory one level upper for setup.py
    dll_path = [curr_path, os.path.join(curr_path, '../../lib/'),
                os.path.join(curr_path, '../../build/'),
                os.path.join(curr_path, './lib/'),
                os.path.join(sys.prefix, 'fmlearn')]
    if sys.platform == 'win32':
        if platform.architecture()[0] == '64bit':
            dll_path.append(os.path.join(curr_path, '../../windows/x64/Release/'))
            # hack for pip installation when copy all parent source directory here
            dll_path.append(os.path.join(curr_path, './windows/x64/Release/'))
        else:
            dll_path.append(os.path.join(curr_path, '../../windows/Release/'))
            # hack for pip installation when copy all parent source directory here
            dll_path.append(os.path.join(curr_path, './windows/Release/'))
        dll_path = [os.path.join(p, 'libfm_learn.dll') for p in dll_path]
    elif sys.platform.startswith('linux') or sys.platform.startswith('freebsd'):
        dll_path = [os.path.join(p, 'libfm_learn.so') for p in dll_path]
    elif sys.platform == 'darwin':
        dll_path = [os.path.join(p, 'fm_learn.dylib') for p in dll_path]
    elif sys.platform == 'cygwin':
        dll_path = [os.path.join(p, 'cygfm_learn.dll') for p in dll_path]

    lib_path = [p for p in dll_path if os.path.exists(p) and os.path.isfile(p)]

    if len(lib_path) == 0:
        raise FMLearnLibraryNotFound("lib path not found")

    return lib_path[0]

