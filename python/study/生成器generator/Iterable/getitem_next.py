# -*- coding: utf-8 -*-
"""
文 件 名: getitem_next.py
文件描述: 即使iterable已经有__next__()方法。因此执行iter(iterable)生成的迭代器调用它的__next__()方法实际上调用的是__getitem__()改写的__next__()方法
备    注: https://blog.csdn.net/m0_59156726/article/details/128953086
作    者: HanKin
创建日期: 2024.01.05
修改日期：2024.01.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
class IteratorC(object):
    """其实这个例子是有问题的，虽然没无语法错误，也不会导致什么错误
    """
    def __init__(self,):
        self.index = 0
        self.number = [1,2,3,4,5]
        self.str = "abcdefg"
 
    def __getitem__(self, item):
        """
        __getitem__()中自动实现了StopIteration()， 而__next__中必须手动添加，当索引越界需要停止。否则for循环最终越界后会报错而不会停止
        """
        print("IteratorC.__getitem__()被调用了")
        return self.number[item]
 
    def __next__(self):
        print("IteratorC.__next__()被调用了")
        try:
            word = self.str[self.index]
        except IndexError:
            raise StopIteration()
        self.index += 1
        return word

Iterator_c = IteratorC()
 
itorc = iter(Iterator_c)
itorc.__next__()

print("**********")
# 只要对象中带有__getitem__()，即可实现使用[]去得到某一个索引值，只要没有__getitem__()必无法实现
print(Iterator_c[2])

print("**********")
for i in Iterator_c:
    print(i)

'''
输出：
IteratorC.__getitem__()被调用了
**********
IteratorC.__getitem__()被调用了
3
**********
IteratorC.__getitem__()被调用了
1
IteratorC.__getitem__()被调用了
2
IteratorC.__getitem__()被调用了
3
IteratorC.__getitem__()被调用了
4
IteratorC.__getitem__()被调用了
5
IteratorC.__getitem__()被调用了
'''