# -*- coding: utf-8 -*-
"""
文 件 名: repr_example.py
文件描述: 学习repr函数
备    注: repr() 函数将对象转化为供解释器读取的形式
作    者: HanKin
创建日期: 2023.12.21
修改日期：2023.12.21

Copyright (c) 2023 HanKin. All rights reserved.
"""

s = 'RUNOOB'
print(s)        # RUNOOB
print(repr(s))  # 'RUNOOB'

dict = {'runoob': 'runoob.com', 'google': 'google.com'}
print(dict)         # {'runoob': 'runoob.com', 'google': 'google.com'}
print(repr(dict))   # {'runoob': 'runoob.com', 'google': 'google.com'}

s="物品\t单价\t数量\n包子\t1\t2"
print(s)        # 物品    单价    数量
                # 包子    1       2
print(repr(s))  # '物品\t单价\t数量\n包子\t1\t2'