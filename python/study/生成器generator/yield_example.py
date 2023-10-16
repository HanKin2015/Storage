# -*- coding: utf-8 -*-
"""
文 件 名: yield_example.py
文件描述: 生成器，yield相当于是一个return语句
作    者: HanKin
创建日期: 2023.10.12
修改日期：2023.10.12

Copyright (c) 2023 HanKin. All rights reserved.
"""

def fab(max): 
    n, a, b = 0, 0, 1 
    while n < max: 
        yield b      # 使用 yield
        # print(b) 
        a, b = b, a + b 
        n = n + 1

for n in fab(5): 
    print(n)

f = fab(5)
while True:
    n = next(f)
    print(n)

"""
1 1 2 3 5
"""