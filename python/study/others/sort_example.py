# -*- coding: utf-8 -*-
"""
文 件 名: sort_example.py
文件描述: sort函数的高级用法，ord函数返回ascii值
作    者: HanKin
创建日期: 2024.04.15
修改日期：2024.04.15

Copyright (c) 2024 HanKin. All rights reserved.
"""
n = int(input()) # 输入菜品数目

# 创建一个空列表，用于存储菜品数据
dishes = []

# 输入菜品数据并存储到列表中
for _ in range(n):
    dish_name, cost, quantity_sold, discount = input().split()
    cost, quantity_sold, discount = float(cost), int(quantity_sold), float(discount)
    dishes.append((dish_name, cost, quantity_sold, discount))
    
# 对菜品数据进行排序
dishes.sort(key=lambda x: (-x[2], x[3], x[1], -ord(x[0][0])))

# 输出排序后的菜品数据
for dish in dishes:
    print(dish[0], dish[1], dish[2], dish[3])

"""
4
c 1 2 3
c 1 1 8
c 1 3 99
m 0 2 3

c 1.0 3 99.0
m 0.0 2 3.0
c 1.0 2 3.0
c 1.0 1 8.0
"""