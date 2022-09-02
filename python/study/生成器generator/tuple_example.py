# -*- coding: utf-8 -*-
"""
文 件 名: tuple_example.py
文件描述: tuple元组
作    者: HanKin
创建日期: 2022.08.24
修改日期：2022.08.24

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time

def main():
    """
    tuple是另一种有序的列表，也称为“元组”。tuple 和 list 非常类似，但是，tuple一旦创建完毕，就不能修改了。
    创建tuple和创建list唯一不同之处是用( )替代了[ ]。
    创建好了 t 就不能改变了，tuple没有 append()方法，也没有insert()和pop()方法。所以，新同学没法直接往 tuple 中添加，老同学想退出 tuple 也不行。
    获取 tuple 元素的方式和 list 是一模一样的，我们可以正常使用 t[0]，t[-1]等索引方式访问元素，但是不能赋值成别的元素。
    """
    
    t = ('Zhangsan', 'Lisi', 'Wangwu')
    print(type(t), t)
    print(t[0], t[-1])
    
    t = ()
    print(type(t), t)

    """
    t 不是tuple ，而是整数1。为什么呢?
    因为()既可以表示tuple，又可以作为括号表示运算时的优先级，结果 (1)被Python解释器计算出结果 1，导致我们得到的不是tuple，而是整数 1。用()定义单元素的tuple造成了歧义，所以 Python 规定，单元素 tuple 要多加一个逗号“,”，这样就避免了歧义。
    """
    t = (1)
    print(type(t), t)
    
    # Python在打印单元素tuple时，也自动添加了一个“,”，为了更明确地告诉你这是一个tuple。多元素 tuple 加不加这个额外的“,”效果是一样的
    t = (1,)
    print(type(t), t)
    t = (1,2,3,)
    print(type(t), t)
    
    # Python之“可变”的tuple
    t = ('a', 'b', ['A', 'B'])
    L = t[2]
    L[0] = 'X'
    L[1] = 'Y'
    print(t)
    L.append('Z')
    print(t)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))