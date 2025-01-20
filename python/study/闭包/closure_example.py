# -*- coding: utf-8 -*-
"""
文 件 名: closure_example.py
文件描述: 闭包是指一个函数可以“记住”并访问其词法作用域中的变量，即使在其外部被调用的情况下。闭包通常用于封装数据和实现工厂函数等场景。
作    者: HanKin
备    注: 
创建日期: 2025.01.19
修改日期：2025.01.19

Copyright (c) 2025 HanKin. All rights reserved.
"""
def outer_function(x):
    # outer_function 是外部函数
    def inner_function(y):
        # inner_function 是内部函数
        return x + y  # 访问外部函数的变量 x
    return inner_function  # 返回内部函数

# 创建闭包
closure = outer_function(10)

# 调用闭包
result1 = closure(5)  # 10 + 5
result2 = closure(20)  # 10 + 20

print(result1)  # 输出: 15
print(result2)  # 输出: 30
