# -*- coding: utf-8 -*-
"""
文 件 名: iter_iterator.py
文件描述: 所谓迭代器，是实现了__next__()方法的对象，所有的迭代器都是可迭代对象，因此也必须包含__iter__() or __getitem__()方法
备    注: https://blog.csdn.net/m0_59156726/article/details/128953086
作    者: HanKin
创建日期: 2024.01.05
修改日期：2024.01.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
class IteratorC(object):
    def __init__(self, text):
        self.text = text
        self.index = 0
 
    def __iter__(self):
        print("IteratorC.__iter__()被调用了")
        return self
 
    def __next__(self):
        print("IteratorC.__next__()被调用了")
        try:
            word = self.text[self.index]
        except IndexError:
            raise StopIteration()
        self.index += 1
        return word

iterator_c = IteratorC("iterator_c")
for i in range(3):
    print(next(iterator_c))

print('*' * 50)

for j in iterator_c:
    print(j)
 
'''
输出：
IteratorC.__next__()被调用了
i
IteratorC.__next__()被调用了
t
IteratorC.__next__()被调用了
e
**************************************************
IteratorC.__iter__()被调用了
IteratorC.__next__()被调用了
r
IteratorC.__next__()被调用了
a
IteratorC.__next__()被调用了
t
IteratorC.__next__()被调用了
o
IteratorC.__next__()被调用了
r
IteratorC.__next__()被调用了
_
IteratorC.__next__()被调用了
c
IteratorC.__next__()被调用了
'''