# -*- coding: utf-8 -*-
"""
文 件 名: dict_update.py
文件描述: 将一个字典合并到另一个字典中，应该使用更新字典的方法，比如使用 update() 方法或者字典解包。
参    考: 
作    者: HanKin
创建日期: 2024.01.23
修改日期：2024.01.23

Copyright (c) 2024 HanKin. All rights reserved.
"""

dic = { "name": "zhangsan", "age": 12 }

new_dic = { **dic, "other": "test", "sex": "male" }
print(new_dic)  # {'name': 'zhangsan', 'age': 12, 'other': 'test', 'sex': 'male'}

messages = { "1": { "x": 1, "y": 2}, "2": { "x": 2, "y": 2}, "3": { "x": 3, "y": 2} }
new_dic = { **messages.get("2"), "other": "test", "sex": "male" }
print(new_dic)  # {'x': 2, 'y': 2, 'other': 'test', 'sex': 'male'}

new_dic = dic.copy()  # 创建原字典的副本
new_dic.update({ "other": "test", "sex": "male" })  # 更新字典
print(new_dic)  # {'name': 'zhangsan', 'age': 12, 'other': 'test', 'sex': 'male'}