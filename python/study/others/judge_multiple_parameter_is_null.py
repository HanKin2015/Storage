# -*- coding: utf-8 -*-
"""
文 件 名: judge_multiple_parameter_is_null.py
文件描述: 判断多个参数是否存在空值
备    注: 
作    者: HanKin
创建日期: 2023.12.06
修改日期：2023.12.06

Copyright (c) 2023 HanKin. All rights reserved.
"""
x = "2"
y = "2"
z = 1
if not all([x, y, z]):
    print("at least one null value exists here")
else:
    print("no null value exists here")

x = "2"
y = ""
z = 1
if not all([x, y, z]):
    print("at least one null value exists here")
else:
    print("no null value exists here")