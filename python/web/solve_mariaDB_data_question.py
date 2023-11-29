# -*- coding: utf-8 -*-
"""
文 件 名: solve_mariaDB_data_question.py
文件描述: 数据库不再收集数据问题
作    者: HanKin
创建日期: 2023.11.23
修改日期：2023.11.23

Copyright (c) 2023 HanKin. All rights reserved.
"""
import json
import requests

filepath = r"D:\迅雷下载\Tools4.5.10\additional_data\common_file\toolTotals.json"
with open(filepath, "r", encoding="utf-8") as f:
    data = json.load(f)
res = requests.post(url="https://11.6.10.54:913/totals", json=data)
print(res.text)
if res.text:
    print("yes")
    with open(filepath, "w", encoding="utf-8") as f:
        f.write("{}")
#nohup python run.py &