# -*- coding: utf-8 -*-
"""
文 件 名: set_intersection.py
文件描述: set交集、并集、差集
作    者: HanKin
备    注: difference_update() 方法可以直接在原集合上进行差集操作，使用 difference() 方法或 - 运算符也可以计算两个集合的差集
创建日期: 2025.01.09
修改日期：2025.01.09

Copyright (c) 2025 HanKin. All rights reserved.
"""
set1 = {1, 2, 3, 4}
set2 = {3, 4, 5, 6}
print(type(set1), type(set2))
 
# 交集
intersection = set1 & set2
 
# 并集
union = set1 | set2
 
# 差集
# set1减set2
difference1 = set1 - set2
 
# set2减set1
difference2 = set2 - set1
 
print("交集:", intersection)        # 交集: {3, 4}
print("并集:", union)               # 并集: {1, 2, 3, 4, 5, 6}
print("set1减set2:", difference1)   # set1减set2: {1, 2}
print("set2减set1:", difference2)   # set2减set1: {5, 6}

print("----- 使用函数 ----")
# 交集
intersection = set1.intersection(set2)
print("交集:", intersection)        # 交集: {3, 4}
set1.intersection_update(set2)
intersection = set1
print("交集:", intersection)        # 交集: {3, 4}
set1 = {1, 2, 3, 4}
 
# 并集
set1.update(set2)
union = set1
print("并集:", union)               # 并集: {1, 2, 3, 4, 5, 6}
set1 = {1, 2, 3, 4}

# 差集
# set1减set2
difference1 = set1.difference(set2)
print("set1减set2:", difference1)   # set1减set2: {1, 2}
set1.difference_update(set2)
difference1 = set1
print("set1减set2:", difference1)   # set1减set2: {1, 2}
set1 = {1, 2, 3, 4}

# set2减set1
difference2 = set2.difference(set1)
print("set2减set1:", difference2)   # set2减set1: {5, 6}
set2.difference_update(set1)
difference2 = set2
print("set2减set1:", difference2)   # set2减set1: {5, 6}