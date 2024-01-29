# -*- coding: utf-8 -*-
"""
文 件 名: find_duplicate_element_in_list.py
文件描述: 在list中找重复元素
备    注: https://www.python100.com/html/P70CZ820SWZ7.html
作    者: HanKin
创建日期: 2023.10.12
修改日期：2023.10.12

Copyright (c) 2023 HanKin. All rights reserved.
"""
from collections import Counter

def find_duplicate_element_in_list1():
    print('*' * 50)
    list = [1, 2, 3, 4, 1, 2, 5, 6, 7, 7, 8, 9]
    duplicate = []
    for item in list:
        if list.count(item) > 1 and item not in duplicate:
            duplicate.append(item)
    print(duplicate)

def find_duplicate_element_in_list2():
    print('*' * 50)
    my_list = [1, 2, 3, 4, 1, 2, 5, 6, 7, 7, 8, 9]
    my_counter = Counter(my_list)   # 使用Counter类来统计每个元素出现的次数
    duplicates = [item for item, count in my_counter.items() if count > 1]
    print(duplicates)   # [1, 2, 3, 5]

def find_duplicate_element_in_list3():
    print('*' * 50)
    lst = [1, 2, 3, 4, 1, 2, 5, 6, 7, 7, 8, 9]
    duplicate = set([x for x in lst if lst.count(x) > 1])
    print(type(duplicate))
    print(list(duplicate))
    print(duplicate)
    
def find_duplicate_element_in_list4():
    print('*' * 50)
    import numpy as np
    list = [1, 2, 3, 4, 1, 2, 5, 6, 7, 7, 8, 9]
    _, index = np.unique(np.array(list), return_index=True)
    duplicate = [item for j, item in enumerate(list) if j not in index]
    print(duplicate)

def find_duplicate_element_in_list5():
    print('*' * 50)
    import pandas as pd
    lst = [1, 2, 3, 4, 1, 2, 5, 6, 7, 7, 8, 9]
    s = pd.Series(lst)
    duplicate = list(s[s.duplicated()])
    print(duplicate)

find_duplicate_element_in_list1()
find_duplicate_element_in_list2()
find_duplicate_element_in_list3()
find_duplicate_element_in_list4()
find_duplicate_element_in_list5()
