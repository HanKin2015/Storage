# -*- coding: utf-8 -*-
"""
文 件 名: dict_is_null.py
文件描述: 字典判空
作    者: HanKin
创建日期: 2023.11.21
修改日期：2023.11.21

Copyright (c) 2023 HanKin. All rights reserved.
"""

detection_list  = []
detection_list.append({"age": 24, "name": "zhangsan"})
detection_list.append({})
print(detection_list)
for item in detection_list:
    print(type(item))

detection_list = [item for item in detection_list if item]
print(detection_list)

sample_dict = {"1": 1}
# 使用if判断
if sample_dict:
    print("字典不为空")
else:
    print("字典为空")
# 使用len()函数
if len(sample_dict) == 0:
    print("字典为空")
else:
    print("字典不为空")
# 使用not关键字
if not sample_dict:
    print("字典为空")
else:
    print("字典不为空")
# 使用bool()函数
if bool(sample_dict):
    print("字典不为空")
else:
    print("字典为空") 
print(dir(dict))
# 使用字典的__len__()方法
if sample_dict.__len__():
    print("字典不为空")
else:
    print("字典为空")