# -*- coding: utf-8 -*-
"""
文 件 名: pickle_example3.py
文件描述: 清空pickler的“备忘”。使用Pickler实例在序列化对象的时候，它会“记住”已经被序列化的对象引用，所以对同一对象多次调用dump(obj)，pickler不会“傻傻”的去多次序列化
作    者: HanKin
创建日期: 2024.03.01
修改日期：2024.03.01

Copyright (c) 2024 HanKin. All rights reserved.
"""
import pickle
import io

class Person:
    def __init__(self, n, a):
        self.name = n
        self.age  = a
        
    def show(self):
        print(self.name + "_" + str(self.age))

aa = Person("JGood", 2)
aa.show()

fle = io.BytesIO()
pick = pickle.Pickler(fle)
pick.dump(aa)
val1 = fle.getvalue()
print(len(val1))

# 这一行会导致不同的结果
#pick.clear_memo()

pick.dump(aa)
val2 = fle.getvalue()
print(len(val2))

test = pick.dump(aa)
print(test)
test = fle.getvalue()
print(test)