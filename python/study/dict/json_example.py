# -*- coding: utf-8 -*-
"""
文 件 名: json_example.py
文件描述: 学习json库
备    注: 
作    者: HanKin
创建日期: 2023.10.11
修改日期：2023.10.11

Copyright (c) 2023 HanKin. All rights reserved.
"""

import json

data = {"name": "张三", "age": 23, "remark": "Љ"}
with open('data1.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=4, ensure_ascii=False)

with open('data2.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, indent=4, ensure_ascii=True)

# UnicodeEncodeError: 'gbk' codec can't encode character '\u0409' in position 1: illegal multibyte sequenc
#with open('data3.json', 'w') as f:
#    json.dump(data, f, indent=4, ensure_ascii=False)

with open('data4.json', 'w') as f:
    json.dump(data, f, indent=4, ensure_ascii=True)

# 使用 4 个空格作为缩进
json_str = json.dumps(data, indent=4, ensure_ascii=False)

# 使用制表符作为缩进
json_str_tab = json.dumps(data, indent="\t", ensure_ascii=True)

print(json_str)
print(json_str_tab)

json_obj = json.loads(json_str)
print(json_obj)
print(type(json_obj))