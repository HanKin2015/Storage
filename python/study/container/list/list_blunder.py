# -*- coding: utf-8 -*-
"""
文 件 名: list_blunder.py
文件描述: TypeError: 'list' object is not callable
备    注: 由于您之前定义了一个名为 list 的变量，Python 解释器将 list 视为一个变量而不是内置的 list 类型，从而导致了这个错误
作    者: HanKin
创建日期: 2024.01.25
修改日期：2024.01.25

Copyright (c) 2024 HanKin. All rights reserved.
"""
list = [1, 2, 3, 4, 1, 2, 5, 6, 7, 7, 8, 9] # 问题出现在这里
duplicate = set([x for x in list if list.count(x) > 1])
print(type(duplicate))
print(list(duplicate))
print(duplicate)
