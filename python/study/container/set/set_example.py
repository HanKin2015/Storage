# -*- coding: utf-8 -*-
"""
文 件 名: set_example.py
文件描述: set就是集合
备    注: https://www.cnblogs.com/xxpythonxx/archive/2023/05/25/17431886.html
作    者: HanKin
创建日期: 2023.10.19
修改日期：2023.11.21

Copyright (c) 2023 HanKin. All rights reserved.
"""
# 集合的创建
set1 = set({1, 2, 3, 4, 5})
set2 = {1, 2, 3, 4, 5}
set3 = set('abc')
print(set1, set2, set3) # {1, 2, 3, 4, 5} {1, 2, 3, 4, 5} {'b', 'c', 'a'}

# add()方法: 用来往集合里添加单个元素，如果已存在，则不会添加
x_set = set()
#x_set.add([4, 5, 6])    # TypeError: unhashable type: 'list'
x_set.update([1, 2, 3])
print(x_set)

# update()方法: 用来迭代的往集合里添加元素
set1 = {1,2,3,4,5}
#set1.update(6)     # TypeError: 'int' object is not iterable
set1.update('7')    # 不能直接添加数字类型，因为数字类型不可迭代
set1.add(8)         # 无问题
print(set1)         # {1, 2, 3, 4, 5, '7', 8}

# 删除集合元素的方法
set1 = {1, 2, 3, 4, 5}
set1.pop()          # 随机删除一个元素，将元素值返回
set1.remove(2)      # 指定删除一个元素，找不到就会报错
set1.clear()        # 清空整个集合
del set1            # 删除整个集合

# 查询集合元素的方法
set1 = {1, 2, 3, 4, 5}
for s in set1:
    print(s)



