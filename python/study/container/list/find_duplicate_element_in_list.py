# -*- coding: utf-8 -*-
"""
文 件 名: find_duplicate_element_in_list.py
文件描述: 在list中找重复元素
作    者: HanKin
创建日期: 2023.10.12
修改日期：2023.10.12

Copyright (c) 2023 HanKin. All rights reserved.
"""
from collections import Counter

my_list = [1, 2, 3, 2, 4, 1, 5, 3, 2, 6, 7, 5, 8, 9, 1]
my_counter = Counter(my_list)   # 使用Counter类来统计每个元素出现的次数
duplicates = [item for item, count in my_counter.items() if count > 1]
print(duplicates)   # [1, 2, 3, 5]
