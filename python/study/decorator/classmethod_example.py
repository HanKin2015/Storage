# -*- coding: utf-8 -*-
"""
文 件 名: classmethod_example.py
文件描述: 类方法可以直接访问和修改类属性，而不需要实例化类
作    者: HanKin
备    注: 
创建日期: 2025.01.08
修改日期：2025.01.08

Copyright (c) 2025 HanKin. All rights reserved.
"""
class MathUtils:
    @classmethod
    def add(cls, a, b):
        return a + b
result = MathUtils.add(5, 3)  # 直接通过类调用
print(result)  # 输出: 8