# -*- coding: utf-8 -*-
"""
文 件 名: getcwd_example.py
文件描述: 获取当前路径
作    者: HanKin
备    注: 
创建日期: 2025.03.31
修改日期：2025.03.31

Copyright (c) 2025 HanKin. All rights reserved.
"""
import os

print(os.getcwd())
print(os.path.join(os.getcwd(), "build"))

"""
(base) D:\Github\Storage\python\study\others>python getcwd_example.py
D:\Github\Storage\python\study\others
D:\Github\Storage\python\study\others\build
"""