# -*- coding: utf-8 -*-
"""
文 件 名: abstractmethod_example.py
文件描述: 抽象类
作    者: HanKin
备    注: 
创建日期: 2025.01.19
修改日期：2025.01.19

Copyright (c) 2025 HanKin. All rights reserved.
"""
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        """计算形状的面积"""
        pass  # 抽象方法没有实现

class Rectangle(Shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def area(self):
        return self.width * self.height  # 实现抽象方法

# 创建 Rectangle 的实例
rectangle = Rectangle(5, 10)
print(rectangle.area())  # 输出: 50

# 尝试实例化 Shape 会引发错误
# shape = Shape()  # TypeError: Can't instantiate abstract class Shape with abstract methods area
