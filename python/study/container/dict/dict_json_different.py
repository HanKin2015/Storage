# -*- coding: utf-8 -*-
"""
文 件 名: dict_json_different.py
文件描述: dict和json的区别
作    者: HanKin
创建日期: 2023.11.29
修改日期：2023.11.29

Copyright (c) 2023 HanKin. All rights reserved.
"""
import json

dict1 = {'name': 'xiaowang', 'age': 18}
dict2 = {"name": "xiaowang", "age": 18}
print(type(dict1), type(dict2))
print(dict1)
print(dict2)

json1 = json.dumps(dict1)
json2 = json.dumps(dict2, ensure_ascii=False)
print(type(json1), type(json2))
print(json1)
print(json2)

json3 = json.loads(json1)
print(type(json3))
print(json3)
if isinstance(json3, dict):
    print("json3 is dict")
else:
    print("json3 is not dict")
"""
(base) D:\Users\User\Desktop>python k.py
<class 'dict'> <class 'dict'>
{'name': 'xiaowang', 'age': 18}
{'name': 'xiaowang', 'age': 18}
<class 'str'> <class 'str'>
{"name": "xiaowang", "age": 18}
{"name": "xiaowang", "age": 18}
<class 'dict'>
{'name': 'xiaowang', 'age': 18}
json3 is dict
"""
