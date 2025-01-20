# -*- coding: utf-8 -*-
"""
文 件 名: list_intersection.py
文件描述: 列表交集、并集、差集
作    者: HanKin
备    注: 
创建日期: 2025.01.07
修改日期：2025.01.07

Copyright (c) 2025 HanKin. All rights reserved.
"""
list1 = [1, 2, 3, 4]
list2 = [3, 4, 5, 6]
 
# 交集
intersection = list(set(list1) & set(list2))
 
# 并集
union = list(set(list1) | set(list2))
 
# 差集
# 列表1减列表2
difference1 = list(set(list1) - set(list2))
 
# 列表2减列表1
difference2 = list(set(list2) - set(list1))
 
print("交集:", intersection)          # 交集: [3, 4]
print("并集:", union)                 # 并集: [1, 2, 3, 4, 5, 6]
print("列表1减列表2:", difference1)   # 列表1减列表2: [1, 2]
print("列表2减列表1:", difference2)   # 列表2减列表1: [5, 6]