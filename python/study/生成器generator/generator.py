# -*- coding: utf-8 -*-
"""
文 件 名: generator.py
文件描述: 学习生成器
作    者: HanKin
创建日期: 2022.08.15
修改日期：2022.08.15

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import sys

# 定义一个斐波那契函数
def fib(times):
    print('----- {}[{}] -----'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    # 初始化
    n = 0
    a, b = 0, 1
    while n < times:
        print(b)
        a, b = b, a+b
        n += 1

def fib_generator(times):
    print('----- {}[{}] -----'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))

    # 初始化
    n = 0
    a, b = 0, 1
    while n < times:
        yield b
        a, b = b, a+b
        n += 1

def main():
    # 列表生成式
    lst = [i for i in range(10)]
    print(lst)
    print(type(lst))
    
    g = (i for i in range(10))
    print(g)        # g是一个生成器对象
    print(type(g))  # g的类型是生成器
    
    # 通过for-in循环打印出来
    for i in g:
        print(i)
    print('*' * 50) # 两者只能二选一
    # 通过 next() 函数
    #while True:
    #    print(next(g))
    # 所以，我们创建了一个生成器后，基本上永远不会调用 next() ，而是通过 for 循环来迭代它，并且不需要关心StopIteration 异常。

    # generator非常强大。如果推算的算法比较复杂，用类似列表生成式的 for 循环无法实 现的时候，还可以用函数来实现。比如，著名的斐波拉契数列（Fibonacci），除第一个和第二个数外，任意一个 数都可由前两个数相加得到
    fib(6)
    
    # 创建生成器的方式2：yield
    g = fib_generator(6)
    print(g)
    #while True:
    #    print(next(g))
    for i in g:
        print(i)
    
    # 遍历生成器的方式
    enumerate_element()

def enumerate_element():
    """
    遍历生成器的方式
    """
    
    print('----- {}[{}] -----'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    # 创建一个生成器
    g = (i for i in range(10))
    
    # 1、通过next（）函数
    print(next(g))
    print(next(g))
    # 0
    # 1
    
    # 2、objict内置的__next__（）方法
    print(g.__next__())
    print(g.__next__())
    # 2
    # 3
    
    # 3、send（）方法，生成器的第一个值必须是send(None),后面没有限制
    print(g.send(None))
    print(g.send(''))
    print(g.send(1))
    # 4
    # 5
    # 6
    
    # 4、通过循环打印 for- in
    for i in g:
        print(i)
        
    '''
    7
    8
    9
    '''

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))