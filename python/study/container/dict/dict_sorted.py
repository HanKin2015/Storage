# -*- coding: utf-8 -*-
"""
文 件 名: dict_sorted.py
文件描述: 字典排序
备    注: 
作    者: HanKin
创建日期: 2024.06.17
修改日期：2024.06.17

Copyright (c) 2024 HanKin. All rights reserved.
"""
# 根据键排序
dict1 = {'banana': 3, 'apple': 4, 'pear': 1, 'orange': 2}
sorted_dict1 = dict(sorted(dict1.items()))
print(sorted_dict1)  # 输出: {'apple': 4, 'banana': 3, 'orange': 2, 'pear': 1}
 
# 根据值排序
dict2 = {'banana': 3, 'apple': 4, 'pear': 1, 'orange': 2}
sorted_dict2 = dict(sorted(dict2.items(), key=lambda item: item[1], reverse=False))
print(sorted_dict2)  # 输出: {'pear': 1, 'orange': 2, 'banana': 3, 'apple': 4}