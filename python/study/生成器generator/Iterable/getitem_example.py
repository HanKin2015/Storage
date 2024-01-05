# -*- coding: utf-8 -*-
"""
文 件 名: getitem_example.py
文件描述: 官方文档给出的解释是实现了__iter__() or __getitem__()方法的对象都叫可迭代对象
备    注: https://blog.csdn.net/m0_59156726/article/details/128953086
作    者: HanKin
创建日期: 2024.01.05
修改日期：2024.01.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
from collections.abc import Iterator, Iterable

class IterableB(object):
    def __init__(self, text):
        self.text = text
 
    def __getitem__(self, item):
        print("IterableB.__getitem__()被调用了")
        return self.text[item]

iterable_b = IterableB("iterable_a")
print(isinstance(iterable_b, Iterable))
itorb = iter(iterable_b)
print('*******', '\n', dir(iterable_b), '\n', dir(itorb), '\n', '*******')
 
for i in iterable_b:
    print(i)