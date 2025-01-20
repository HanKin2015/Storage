# -*- coding: utf-8 -*-
"""
文 件 名: classmethod_example.py
文件描述: classmethod以及cls的作用
作    者: HanKin
备    注: 
创建日期: 2025.01.20
修改日期：2025.01.20

Copyright (c) 2025 HanKin. All rights reserved.
"""
class Test:
    def __init__(self):
        self.DETECTION_LIST1 = []
        self.DETECTION_LIST2 = []

    @classmethod
    def set_detection_list1(cls, detection_list):
        cls.DETECTION_LIST1 = detection_list

    def set_detection_list2(self, detection_list):
        self.DETECTION_LIST2 = detection_list

test = Test()
test.set_detection_list1([1, 2, 3])
print(len(test.DETECTION_LIST1))    # 0

test.set_detection_list2([1, 2, 3])
print(len(test.DETECTION_LIST2))    # 3

Test.set_detection_list1([1, 2, 3])
print(len(Test.DETECTION_LIST1))    # 3