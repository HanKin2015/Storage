# -*- coding: utf-8 -*-
"""
文 件 名: with_example.py
文件描述: with语句的用法
备    注: https://blog.csdn.net/knighthood2001/article/details/120624571
作    者: HanKin
创建日期: 2024.01.04
修改日期：2024.01.04

Copyright (c) 2024 HanKin. All rights reserved.
"""
class Door1():
    """没有实现上下文管理
    """
    def open(self):
        print('Door is opened')
    def close(self):
        print('Door is closed')

def test1():
    """报错AttributeError: __enter__
    """
    with Door1() as d:
        d.open()
        d.close()

class Door2():
    """实现上下文管理
    """
    def __enter__(self):
        print('Begin')
        return self
 
    def __exit__(self, exc_type, exc_value, traceback):
        if exc_type:
            print('Error')
        else:
            print('End')
    def open(self):
        print('Door is opened')
    def close(self):
        print('Door is closed')

def test2():
    """
    Begin
    Door is opened
    Door is closed
    End
    """
    with Door2() as d:
        d.open()
        d.close()

from contextlib import closing
def test3():
    """一个对象没有实现上下文，我们就不能把它用于with语句。这个时候，可以
    用contextlib中的closing()来把该对象变为上下文对象
    Door is opened
    Door is closed（注意会多搞一发）
    Door is closed
    """
    with closing(Door1()) as d:
        d.open()
        d.close()

if __name__ == '__main__':
    test3()