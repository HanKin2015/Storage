# -*- coding: utf-8 -*-
"""
文 件 名: check_json_valid.py
文件描述: 检查json文件合法性
作    者: HanKin
备    注: 
创建日期: 2025.05.28
修改日期：2025.05.28

Copyright (c) 2025 HanKin. All rights reserved.
"""
import json

# 检查json文件合法性
with open("dict.json", "r") as f:
    content = json.load(f)

with open("list.json", "r") as f:
    content = json.load(f)