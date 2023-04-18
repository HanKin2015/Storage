# -*- coding: utf-8 -*-
"""
文 件 名: decorator_example.py
文件描述: 装饰器
作    者: HanKin
创建日期: 2023.04.18
修改日期：2023.04.18

Copyright (c) 2023 HanKin. All rights reserved.
"""

def my_decorator(func):
    def wrapper():
        print("Before the function is called.")
        func()
        print("After the function is called.")
    return wrapper

@my_decorator
def say_hello():
    print("Hello!")

say_hello()
