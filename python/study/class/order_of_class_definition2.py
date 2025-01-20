# -*- coding: utf-8 -*-
"""
文 件 名: order_of_class_definition1.py
文件描述: 使用字符串延迟引用
作    者: HanKin
备    注: 
创建日期: 2025.01.19
修改日期：2025.01.19

Copyright (c) 2025 HanKin. All rights reserved.
"""
class Son3:
    def __init__(self):
        self.father = Father3()  # 在实例化时创建 Father3 的实例
        print("Son3 initialized")

class Father3:
    def __init__(self):
        print("Father3 initialized")

# 创建 Son3 的实例
son_instance = Son3()

"""
(base) D:\Users\User\Desktop>python order_of_class_definition1.py
Father3 initialized
Son3 initialized
"""
