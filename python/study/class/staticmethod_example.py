# -*- coding: utf-8 -*-
"""
文 件 名: staticmethod_example.py
文件描述: 要正确使用 @staticmethod，你需要将其放在一个类中
作    者: HanKin
备    注: 
创建日期: 2025.06.27
修改日期：2025.06.27

Copyright (c) 2025 HanKin. All rights reserved.
"""

"""
from abc import ABC, abstractmethod

@staticmethod
def is_debian():
    return True

is_debian()
"""

from abc import ABC, abstractmethod

class MyClass(ABC):
    @staticmethod
    def is_debian():
        return True

# 调用静态方法
result = MyClass.is_debian()
print(result)  # 输出: True
