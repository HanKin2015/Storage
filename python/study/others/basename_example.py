# -*- coding: utf-8 -*-
"""
文 件 名: basename_example.py
文件描述: 获取绝对路径中的末尾文件夹
作    者: HanKin
创建日期: 2024.06.05
修改日期：2024.06.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
 
# 假设你有一个文件夹路径
folder_path = "/path/to/your/folder"
 
# 使用os.path.basename获取文件夹名
folder_name = os.path.basename(folder_path)
 
print(folder_name)