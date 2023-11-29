# -*- coding: utf-8 -*-
"""
文 件 名: reduce_example.py
文件描述: 学习reduce函数
备    注: https://baijiahao.baidu.com/s?id=1773439374793622815&wfr=spider&for=pc
作    者: HanKin
创建日期: 2023.11.27
修改日期：2023.11.27

Copyright (c) 2023 HanKin. All rights reserved.
"""
from functools import reduce
import operator

numbers = [1, 2, 3, 4, 5]

# 使用自定义函数（二元操作函数：求奇数元素的乘积）
def multiply_odd_numbers(x, y):
    if y % 2 == 1:
        return x * y
    return x
result = reduce(multiply_odd_numbers, numbers)
print("Product of odd numbers:", result) # 输出：Product of odd numbers: 15

# 使用reduce()函数求累加和
sum_result = reduce(operator.add, numbers)
print("Sum of numbers:", sum_result) # 输出：Sum of numbers: 15

# 使用reduce()函数求累乘
product_result = reduce(operator.mul, numbers)
print("Product of numbers:", product_result) # 输出：Product of numbers: 120

# 指定初始值为10
result2 = reduce(operator.add, numbers, 10)
print("Result with initial value:", result2) # 输出：Result with initial value: 25

# 使用reduce()函数将列表中的元素连接成一个字符串
words = ["Hello", " ", "Python", "!"]
result = reduce(lambda x, y: x + y, words)
print("Concatenated string:", result) # 输出：Concatenated string: Hello Python!

# 使用reduce()函数结合lambda函数将列表元素相加得到整数
result = reduce(lambda x, y: x * 10 + y, numbers)
print("Concatenated number:", result) # 输出：Concatenated number: 12345

# 使用reduce()函数结合lambda函数求列表中的最大值和最小值
max_value = reduce(lambda x, y: x if x > y else y, numbers)
min_value = reduce(lambda x, y: x if x < y else y, numbers)
print("Max value:", max_value) # 输出：Max value: 5
print("Min value:", min_value) # 输出：Min value: 1