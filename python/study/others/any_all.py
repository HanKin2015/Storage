# -*- coding: utf-8 -*-
"""
文 件 名: any_all.py
文件描述: 学习any和all函数
作    者: HanKin
创建日期: 2023.11.21
修改日期：2023.11.21

Copyright (c) 2023 HanKin. All rights reserved.
"""
lst1 = [1, 2, 3, 0]
lst2 = [4, 5, 0]
lst3 = [6, 7, 8, 9, 0]

# 对于迭代中的任何 x，如果 bool(x) 是 True，返回 True。如果迭代是空，返回 False。
element = 7
if any(element in lst for lst in [lst1, lst2, lst3]):
    print("yes")

# 如果 bool(x) 对于可迭代对象中的所有值 x 为 True，则返回 True。如果可迭代对象为空，则返回 True。
element = 0
if all(element in lst for lst in [lst1, lst2, lst3]):
    print("yes")