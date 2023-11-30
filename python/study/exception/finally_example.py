# -*- coding: utf-8 -*-
"""
文 件 名: finally_example.py
文件描述: 不管抛不抛异常都会走到finally语句
作    者: HanKin
创建日期: 2023.11.29
修改日期：2023.11.29

Copyright (c) 2023 HanKin. All rights reserved.
"""
import traceback
for i in range(2):
    ret = -1
    try:
        ret = 5 / i
    except:
        print(traceback.format_exc())
    finally:
        print(i, ret)
