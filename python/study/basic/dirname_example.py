# -*- coding: utf-8 -*-
"""
文 件 名: dirname_example.py
文件描述: 去掉文件名，返回目录
作    者: HanKin
创建日期: 2024.01.23
修改日期：2024.01.23

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os

# 项目根目录,拼接路径时"\\"常用于绝对路径，使用"/"可以不加转义符"\"，综上所述"\\"或者"/"都可以
basedir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))

# 即使有__main__函数，但是还是会从上到下优先输出
print(__file__)
print(os.path.dirname(__file__))
print(os.path.abspath(os.path.dirname(__file__)))
print(os.path.dirname(os.path.dirname(__file__)))
print(basedir)

if __name__ == '__main__':
    print("*" * 50)
    print(__file__) # __file__输出的是执行的文件名，如果是python a.py则是a.py，如果python D:/Users/User?Desktop/a.py
    print(os.path.dirname(__file__))                    # 返回文件的目录位置
    print(os.path.abspath(os.path.dirname(__file__)))   # 以防执行的文件路径是相对路径
    print(os.path.dirname(os.path.dirname(__file__)))   # 这里返回到上一层目录位置了
    print(basedir)