# -*- coding: utf-8 -*-
"""
文 件 名: replace_for_expression.py
文件描述: 替代for循环，让Python代码更pythonic !数
备    注: https://mp.weixin.qq.com/s/I8EWnu-YZHj6j4-Ry4brmQ
作    者: HanKin
创建日期: 2023.11.23
修改日期：2023.11.23

Copyright (c) 2023 HanKin. All rights reserved.
"""

item_list = [1, 2, 3, 4, 5]
def do_something_with(item):
    return item * 2

# 1.List Comprehension / Generator Expression（列表推导式和生成器表达式）
result = []
for item in item_list:
    new_item = do_something_with(item)
    result.append(new_item)
print(result)   # [2, 4, 6, 8, 10]
result = [do_something_with(item) for item in item_list]
print(result)   # [2, 4, 6, 8, 10]
result = (do_something_with(item) for item in item_list)
print(result)   # <generator object <genexpr> at 0x00000272A31D71C8>
for elem in result:
    print(elem) # [2, 4, 6, 8, 10]

# 2.函数将一个数组映射成另外数组
old_list = [1, 2, 3, 4, 5]
new_list = map(lambda x: x * 2, old_list)
print(new_list) # <map object at 0x00000224EC327C88>
for elem in new_list:
    print(elem) # [2, 4, 6, 8, 10]

from functools import reduce
numbers = [1, 2, 3, 4, 5]
summation = reduce(lambda x, y: x + y, numbers)
print(summation)# 15

# 许多 Python 内置函数都会使用 iterables
a = list(range(10))
print(a)        # [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
print(all(a))   # False
print(any(a))   # True
print(max(a))   # 9
print(min(a))   # 0
print(list(filter(bool, a)))    # [1, 2, 3, 4, 5, 6, 7, 8, 9]
print(set(a))                   # {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
print(dict(zip(a,a)))           # {0: 0, 1: 1, 2: 2, 3: 3, 4: 4, 5: 5, 6: 6, 7: 7, 8: 8, 9: 9}
print(sorted(a, reverse=True))  # [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
print(str(a))                   # '[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]'
print(sum(a))                   # 45

# 3.Extract Functions or Generators
results = []
for item in item_list:
    # setups
    # condition
    # processing
    # calculation
    results.append(result)
    
def process_item(item):
    # setups
    # condition
    # processing
    # calculation
    return result
results = [process_item(item) for item in item_list]

results = []
for i in range(10):
    for j in range(i):
        results.append((i, j))
results = [(i, j)
           for i in range(10)
           for j in range(i)]

# finding the max prior to the current item
a = [3, 4, 6, 2, 1, 9, 0, 7, 5, 8]
results = []
current_max = 0
for i in a:
    current_max = max(i, current_max)
    results.append(current_max)
# results = [3, 4, 6, 6, 6, 9, 9, 9, 9, 9]
def max_generator(numbers):
    current_max = 0
    for i in numbers:
        current_max = max(i, current_max)
        yield current_max
a = [3, 4, 6, 2, 1, 9, 0, 7, 5, 8]
results = list(max_generator(a))
from itertools import accumulate
a = [3, 4, 6, 2, 1, 9, 0, 7, 5, 8]
resutls = list(accumulate(a, max))
# 另外，如果要迭代组合序列，则需要使用product()， permutations()， combinations()。