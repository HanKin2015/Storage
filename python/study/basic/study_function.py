# -*- coding: utf-8 -*-
"""
Created on Tue Dec 21 13:21:21 2021

@author: Administrator
@url   : https://mp.weixin.qq.com/s/vOzmMNMEvS4Fz0TcRB6V1Q
"""


def do_something1(opt: print('参数 opt'), arg=print('参数 arg')) -> print('函数的返回值'):
    print("do something runing1")

# 通常情况下，参数都是不可变类型，如果传入可变类型，可能每次的函数调用，其结果都会被改变
# 调用两次函数 do_something，虽然并没有传入 arg 参数，arg 的值已经发送了变化。如果不注意这点，可能会有 bug 发生。在 Pythcarm 中，会警告我们 arg 是可变对象
def do_something2(opt: print("参数 opt"), arg=[]) -> print("函数的返回值"):
    print("do something runing2")
    print(f"arg = {arg}")
    arg.append(0)

def daily_food(arg, *args, **kwargs):
    print(f"this is a common arg: {arg}")
    print(args)
    print(kwargs)

def do_something3(opt: 1, arg=2) -> 3:
    print("do something runing3")
    print(f"arg = {arg}")
    arg.append(0)

# 魔法参数
def sum(*args):
    print(args)
    print(type(args)) # 元组类型
    su = 0
    for arg in args:
        su += arg
    print(su)



if __name__ == '__main__':
    print('main')
    do_something1('hj')
    do_something2(opt=1)
    do_something2(opt=1)
    
    daily_food("大鸡腿", 2, 3, food1="apple", food2="ice cream")
    
    # 如果要获取函数的类型提示、默认值，可以这样
    print(f"do_something3.__annotations__ = {do_something3.__annotations__}")
    print(f"do_something3.__defaults__ = {do_something3.__defaults__}")
    
    sum(2,3,4)
    sum(2,3,4,5)
    sum(2,3,4,5,6)
    pass