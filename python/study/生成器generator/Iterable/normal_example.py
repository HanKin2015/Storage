# -*- coding: utf-8 -*-
"""
文 件 名: normal_example.py
文件描述: 一个正常的例子
备    注: https://blog.csdn.net/m0_59156726/article/details/128953086
作    者: HanKin
创建日期: 2024.01.05
修改日期：2024.01.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
from collections.abc import Iterator, Iterable

class IterableA(object):
    def __init__(self, text):
        self.text = text
 
    def __iter__(self):
        print("__iter__()被调用了")
        return iter(self.text)

iterable_a = IterableA("iterable_a")
print(isinstance(iterable_a, Iterable))
itora = iter(iterable_a)
print(itora)
for i in iterable_a:
    print(i)

"""
输出：
True
__iter__()被调用了
<str_iterator object at 0x000001BDA55A7700>
__iter__()被调用了
i
t
e
r
a
b
l
e
_
a
"""
