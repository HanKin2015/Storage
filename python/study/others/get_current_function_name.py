# -*- coding: utf-8 -*-
"""
文 件 名: get_current_function_name.py
文件描述: 获取当前函数的名称
作    者: HanKin
备    注: 
创建日期: 2025.01.20
修改日期：2025.01.20

Copyright (c) 2025 HanKin. All rights reserved.
"""
import inspect

def current_function_name():
    # 获取当前调用的帧
    frame = inspect.currentframe()
    # 获取当前函数的名称
    function_name = frame.f_code.co_name
    return function_name

def example_function():
    print("当前函数名是:", current_function_name())
    print("当前函数名是:", example_function.__name__)
    print("当前函数名是:", inspect.currentframe().f_code.co_name)

example_function()

"""
(base) D:\Github\Storage\python\study\others>python get_current_function_name.py
当前函数名是: current_function_name
当前函数名是: example_function
当前函数名是: example_function
"""