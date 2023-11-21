# -*- coding: utf-8 -*-
"""
文 件 名: judge_element_isin_multiple_list.py
文件描述: 判断元素在多个列表中是否存在
作    者: HanKin
创建日期: 2023.11.21
修改日期：2023.11.21

Copyright (c) 2023 HanKin. All rights reserved.
"""
lst1 = [1, 2, 3]
lst2 = [4, 5]
lst3 = [6, 7, 8, 9]

element = 7

# 循环遍历
if element in lst1 or element in lst2 or element in lst3:
    print("yes")

# 使用列表推导式和any()函数（推荐）
if any(element in lst for lst in [lst1, lst2, lst3]):
    print("yes")

# 使用set集合
all_elements = set()
all_elements.update(item for lst in [lst1, lst2, lst3] for item in lst)
if element in all_elements:
    print("yes")

# 使用extend函数不去重
all_elements = []
all_elements.extend(lst1)
all_elements.extend(lst2)
all_elements.extend(lst3)
if element in all_elements:
    print("yes")