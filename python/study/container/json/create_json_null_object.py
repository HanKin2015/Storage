# -*- coding: utf-8 -*-
"""
文 件 名: create_json_null_object.py
文件描述: 创建json空对象
作    者: HanKin
创建日期: 2024.07.18
修改日期：2024.07.18

Copyright (c) 2024 HanKin. All rights reserved.
"""
import json

with open("./extra_info.json", encoding='utf-8') as f:
    extra_info = json.load(f)
    #if isinstance(extra_info, str):
    #    extra_info = dict()

print(type(extra_info))
print(extra_info)

latency_mid = extra_info.get("latency_mid", "")
print(latency_mid)