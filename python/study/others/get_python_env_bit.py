# -*- coding: utf-8 -*-
"""
文 件 名: get_python_env_bit.py
文件描述: 获取python环境位数
参    考: 
作    者: HanKin
创建日期: 2024.01.24
修改日期：2024.01.24

Copyright (c) 2024 HanKin. All rights reserved.
"""
import platform
import sys
import ctypes
import struct
import inspect

get_line = lambda :inspect.getframeinfo(inspect.stack()[1][0]).lineno
get_file = inspect.__file__
get_func = lambda :inspect.getframeinfo(inspect.stack()[1][0]).function

def get_python_env_bit1():
    print(get_func())

    # 获取python的位数
    bit_number = platform.architecture()[0]
    print(bit_number)

    if bit_number == '32bit':
        print("该python环境是32位")
    elif bit_number == '64bit':
        print("该python环境是64位")
    else:
        print("无法确定python环境的位数")
    
def get_python_env_bit2():
    print(get_func())
    
    if sys.maxsize > 2**32:
        print("该python环境是64位")
    else:
        print("该python环境是32位")

def get_python_env_bit3():
    print(get_func())

    # 检64位环境下特有的内存范围
    try:
        ctypes.windll.kernel32.GetSystemWow64DirectoryW
    except AttributeError:
        print("该电脑环境是32位")
    else:
        print("该电脑环境是64位")

def get_python_env_bit4():
    print(get_func())
    print(ctypes.sizeof(ctypes.c_voidp) * 8)
    
def get_python_env_bit5():
    print(get_func())
    print(sys._getframe().f_code.co_name)
    print(sys._getframe().f_lineno)
    
    print(struct.calcsize('P') * 8)

if __name__ == '__main__':
    get_python_env_bit1()
    get_python_env_bit2()
    get_python_env_bit3()
    get_python_env_bit4()
    get_python_env_bit5()
    