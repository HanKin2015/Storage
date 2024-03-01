# -*- coding: utf-8 -*-
"""
文 件 名: pickle_example2.py
文件描述: 要注意的是，在load(file)的时候，要让python能够找到类的定义，否则会报错
作    者: HanKin
创建日期: 2024.03.01
修改日期：2024.03.01

Copyright (c) 2024 HanKin. All rights reserved.
"""
import pickle

class Person:
    def __init__(self, n, a):
        self.name = n
        self.age  = a
        
    def show(self):
        print(self.name + "_" + str(self.age))

aa = Person("JGood", 2)
aa.show()
f = open('d:\\p.txt', 'wb')
pickle.dump(aa, f, 0)
f.close()

# 在加载对象之前，类Person被删除了，这会导致无法正确加载对象
#del Person

f=open('d:\\p.txt', 'rb')
bb=pickle.load(f)
f.close()
bb.show()