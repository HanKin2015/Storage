# -*- coding: utf-8 -*-
"""
文 件 名: iter_and_getitem_different.py
文件描述: iter和getitem实现的迭代对象的不同之点
备    注: https://blog.csdn.net/m0_59156726/article/details/128953086
作    者: HanKin
创建日期: 2024.01.05
修改日期：2024.01.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
class IterableC(object):
    """
    如果iterable中没有__iter__()方法呢，它会去找__getitem__()方法，但是__getitem__()方法并不会被调用，
    找到后会自动根据__getitem__(self, item)中的参数（索引值）及返回值生成迭代器，而__iter__()是返回迭代器
    """
    def __init__(self, text):
        self.text = text
 
    def __getitem__(self, item):
        print("IterableC.__getitem__()被调用了")
        return self.text[item]

class IterableA(object):
    def __init__(self, text):
        self.text = text
 
    def __iter__(self):
        print("IterableA.__iter__()被调用了")
        return iter(self.text)

class IterableB(object):
    """
    当__iter__()和__getitem__()同时存在呢，不好意思，__iter__()的优先级更高，但是正常情况下应该只会存在一个
    """
    def __init__(self, text):
        self.text = text
 
    def __iter__(self):
        print("IterableB.__iter__()被调用了")
        return iter([1,2,3])
 
    def __getitem__(self, item):
        print("IterableB.__getitem__()被调用了")
        return self.text[item]
 
iterable_c = IterableC("iterable_C")
itorc = iter(iterable_c)
print(type(itorc))
 
iterable_a = IterableA("iterable_A")
itora = iter(iterable_a)
print(type(itora))

iterable_b = IterableB("iterable_B")
itorb = iter(iterable_b)
print(type(itorb))
for i in iterable_b:
    print(i)

'''
输出：
<class 'iterator'>
IterableA.__iter__()被调用了
<class 'str_iterator'>
IterableB.__iter__()被调用了
<class 'list_iterator'>
IterableB.__iter__()被调用了
1
2
3
'''
 