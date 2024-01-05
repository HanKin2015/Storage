# -*- coding: utf-8 -*-
"""
文 件 名: error_example.py
文件描述: 一个错误的例子
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
        return self.text
 
iterable_a = IterableA("iterable_a")
print(isinstance(iterable_a, Iterable))

itora = iterable_a.__iter__()
print(itora)

"""
可以发现for 循环执行的时候，iterable_a 的__iter__()被调用了，报错类型和iter()一样，原因是在执行for循环其实是执行了for i in iter(iterable_a)，所以for循环干了两件事：第一个调用了iter()让可迭代对象变成了一个迭代器（不管这个可迭代对象是否是迭代器，都调用一次iter()），第二个循环调用迭代器的__next__()函数。但是由于第一步就失败了，就谈不上第二步骤了。如果迭代器中没有__next__()函数呢？这里是不是觉得迭代器必须要有__next__()方法?答案是肯定的，只要是迭代器必须实现__next__()方法。
"""
for i in iterable_a:
    print(i)

# iter()函数要求参数是可迭代对象型（iterable），返回要求迭代器类型（iterator）
itora = iter(iterable_a)    # TypeError: iter() returned non-iterator of type 'str'


