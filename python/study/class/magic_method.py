# -*- coding: utf-8 -*-
"""
文 件 名: magic_method.py
文件描述: 魔法方法
备    注: https://www.cnblogs.com/CircleWang/p/17241378.html
作    者: HanKin
创建日期: 2024.01.04
修改日期：2024.01.04

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
print(dir(os.path.exists))
#print(help(os.path.exists))

import tqdm
print(dir(tqdm.tqdm))
#print(help(tqdm.tqdm))

class Person:
    def __init__(self, name, age):
        self.name = name
        self.age  = age

    def __str__(self):  # Tom and 20
        return f'{self.name} and {self.age}'

    def __add__(self, other):
        return Person('robot', self.age + other.age)

    def __call__(self, x, y):
        return x.age + y.age

class Demo:
    """测试__del__方法，由于之前的Person类被调用太多次数影响测试
    """
    def __init__(self, name):
        self.name = name

    def mz(self):
        print("这个人是[%s]" % self.name)

    def __del__(self):
        print("[%s]生命周期完了" % self.name)

    def __str__(self):
        return "%s" % self.name

if __name__ == '__main__':
    person = Person('Tom', 20)
    print(person.name, person.age)
    print(person)   # 没有__str__方法时输出<__main__.Person object at 0x000001EAAC087508>
    
    jack = Person('Jack', 55)
    robot = person + jack
    print(robot)   # robot and 75
    
    sum = robot(person, jack)
    print(sum)  # 75
    
    print(robot.__dict__)   # {'name': 'robot', 'age': 75}
    print(Person.__dict__)
    print(Demo.__dict__)
    print(dir(Demo))
    print(help(Demo))
    
    tom = Demo("Tom")
    tom.mz()
    print(tom)
    del tom # del删除一个对象会立即调用__del__方法

    Jerry = Demo("Jerry")
    Jerry.mz()
    print(Jerry)

    print("-" * 50)
    