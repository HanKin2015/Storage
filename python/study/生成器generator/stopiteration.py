# -*- coding: utf-8 -*-
"""
文 件 名: stopiteration.py
文件描述: 学习StopIteration异常
作    者: HanKin
创建日期: 2022.08.22
修改日期：2022.08.22

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import sys

class MyNumbers:
    def __iter__(self):
        self.a = 1
        return self

    def __next__(self):
        if self.a <= 20:
            x = self.a
            self.a += 1
            return x
        else:
            raise StopIteration

def test1():
    myclass = MyNumbers()
    myiter = iter(myclass)

    #for x in myiter:
    #    print(x)
    while True:
        #x = next(myiter)
        #print(x)
        print(myiter.__next__())

def test2():
    # 首先获得Iterator对象:
    it = iter([1, 2, 3, 4, 5])
    # 循环:
    while True:
        try:
            # 获得下一个值:
            x = next(it)
            print(x)
        except StopIteration:
            # 遇到StopIteration就退出循环
            print('except StopIteration')
            break

def main():
    test1()
    test2()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))