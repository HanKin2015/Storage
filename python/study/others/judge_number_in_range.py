# -*- coding: utf-8 -*-
"""
文 件 名: judge_number_in_range.py
文件描述: 判断数字在某个区间的多种方法
备    注: 
作    者: HanKin
创建日期: 2023.11.23
修改日期：2023.11.23

Copyright (c) 2023 HanKin. All rights reserved.
"""
# 方法一：使用比较运算符
num = 7
if 5 <= num <= 10:
    print("数字在5到10之间")
else:
    print("数字不在5到10之间")

# 方法二：使用and逻辑运算符
num = 7
if num >= 5 and num <= 10:
    print("数字在5到10之间")
else:
    print("数字不在5到10之间")

# 方法三：使用范围判断(推荐，注意左闭右开)
num = 7
if num in range(5, 11):
    print("数字在5到10之间")
else:
    print("数字不在5到10之间")

for i in range(5, 10):
    print(i)    # 5, 6, 7, 8, 9