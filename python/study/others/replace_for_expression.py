# -*- coding: utf-8 -*-
"""
文 件 名: replace_for_expression.py
文件描述: 替代for循环，让Python代码更pythonic !数
备    注: https://mp.weixin.qq.com/s/I8EWnu-YZHj6j4-Ry4brmQ
作    者: HanKin
创建日期: 2023.11.22
修改日期：2023.11.22

Copyright (c) 2023 HanKin. All rights reserved.
"""

item_list = [1, 2, 3, 4, 5]
def do_something_with(item):
    return item * 2

# 1.List Comprehension / Generator Expression（列表推导式和生成器表达式）
result = []
for item in item_list:
    new_item = do_something_with(item)
    result.append(item)
print(result)
result = [do_something_with(item) for item in item_list]
print(result)
result = (do_something_with(item) for item in item_list)
print(result)

