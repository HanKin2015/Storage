# -*- coding: utf-8 -*-
"""
文 件 名: enum_example.py
文件描述: 在 Python 中，枚举（Enum）是一种用于定义一组命名常量的类。使用枚举可以使代码更加清晰和可读，特别是在需要使用一组固定值的情况下。
作    者: HanKin
备    注: 
创建日期: 2025.01.19
修改日期：2025.01.19

Copyright (c) 2025 HanKin. All rights reserved.
"""
from enum import Enum
from enum import auto

class Status(Enum):
    PENDING = 1
    COMPLETED = 2
    FAILED = 3

# 使用 auto() 函数自动为枚举成员赋值
class Color(Enum):
    RED = auto()
    GREEN = auto()
    BLUE = auto()

# 使用枚举
print(Color.RED)          # 输出: Color.RED
print(Color.GREEN.name)   # 输出: GREEN
print(Color.BLUE.value)   # 输出: 3

# 遍历枚举
for color in Color:
    print(color)

# 检查成员类型
print(isinstance(Status.PENDING, Status))  # 输出: True

# 检查成员的唯一性
print(Status.PENDING is Status.PENDING)  # 输出: True
