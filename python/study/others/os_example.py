# -*- coding: utf-8 -*-
"""
文 件 名: os_example.py
文件描述: 获取当前路径
作    者: HanKin
备    注: 
创建日期: 2025.03.31
修改日期：2025.03.31

Copyright (c) 2025 HanKin. All rights reserved.
"""
import os

# 从 Python 3.x某个版本 开始，os 模块不再包含 errno 属性，因此在较新版本的 Python 中会出现 AttributeError
print(os.errno)
print(os.errno.EEXIST)

# 推荐直接使用 errno 模块
import errno

print(errno)
print(errno.EEXIST)