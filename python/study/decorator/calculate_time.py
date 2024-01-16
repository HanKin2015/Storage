# -*- coding: utf-8 -*-
"""
文 件 名: calculate_time.py
文件描述: 代码执行时间统计
参    考: 
作    者: HanKin
创建日期: 2024.01.15
修改日期：2024.01.15

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time

def calculate_time(func):
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        print("函数 {} 执行时间为: {} 秒".format(func.__name__, end_time - start_time))
        return result
    return wrapper

@calculate_time
def test():
    time.sleep(3)

test()

r"""
(base) D:\Users\User\Desktop>python k.py
函数 test 执行时间为: 3.0428130626678467 秒
"""