# -*- coding: utf-8 -*-
"""
文 件 名: socket_client_example.py
文件描述: 需使用cythonize命令进行编译
作    者: HanKin
创建日期: 2023.12.02
修改日期：2023.12.02

Copyright (c) 2023 HanKin. All rights reserved.
"""
cdef int a, b, i

def fibonacci(n):
    if n <= 0:
        raise ValueError("n必须是正整数")

    if n == 1:
        return 0
    elif n == 2:
        return 1
    else:
        a = 0
        b = 1
        for i in range(3, n + 1):
            a, b = b, a + b
        return b