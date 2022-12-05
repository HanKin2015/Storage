# -*- coding: utf-8 -*-
"""
文 件 名: format_print.py
文件描述: 格式化输出
作    者: HanKin
创建日期: 2022.11.17
修改日期：2022.11.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

def fab(max): 
    n, a, b = 0, 0, 1 
    while n < max: 
        yield b      # 使用 yield
        # print b 
        a, b = b, a + b 
        n = n + 1

for n in fab(5): 
    print n

print('%d小时%d分%d秒' % (10.1, 20.2, 30.3))