# -*- coding: utf-8 -*-
"""
文 件 名: magic_argument.py
文件描述: 两种魔法参数 *args和**kwargs的用法（假如函数接收的参数过多，这两个魔法方法就能够优雅的简化我们的代码）
备    注: https://blog.csdn.net/weixin_44333824/article/details/106108811
作    者: HanKin
创建日期: 2024.01.03
修改日期：2024.01.03

Copyright (c) 2024 HanKin. All rights reserved.
"""
def sum1(arg1, arg2):
    """带有两个常规参数的求和函数
    """
    print(arg1 + arg2)

def sum2(*args):
    """如果要求5个参数求和，那就需要更改函数内部代码，使其变得更加累赘
    """
    print(args)
    print(type(args)) # 元组类型
    su = 0
    for arg in args:
        su += arg
    print(su)

def daily_food(arg, *args, **kwargs):
    """注意！参数的顺序不能出错，普通变量只能放在魔法变量的后面，否则会报错！
    """
    print(f"this is a common arg: {arg}")
    print(args)
    print(kwargs)

if __name__ == '__main__':
    sum1(2, 3)          # 5
    
    sum2(2, 3, 4)       # 9
    sum2(2, 3, 4, 5)    # 14
    sum2(2, 3, 4, 5, 6) # 20
    
    # 还可以通过传将list，tuple，set类型作为参数传入函数，但是传入参数之前必须要在传入的引用变量前加*
    tuple_ = (1, 2, 3)
    list_  = [1, 2, 3]
    set_   = {1, 2, 3}
    sum2(*tuple_)       # 6
    sum2(*list_)        # 6
    sum2(*set_)         # 6

    daily_food("大鸡腿", 2, 3, food1="apple", food2="ice cream")

    # 可以把字典作为输入传给**kwargs
    food = {"food1": "apple", "food2": "ice cream"}
    daily_food("大鸡腿", 2, 3, **food) # 需要在变量前加 **
