# -*- coding: utf-8 -*-
"""
文 件 名: secure_filename_example.py
文件描述: 学习secure_filename函数
备    注: secure_filename()函数的主要作用是处理文件路径，确保Web应用的安全性。该函数通过将路径中的'/'替换为下划线，防止潜在的路径遍历攻击，从而保护Web应用免受黑客攻击。
作    者: HanKin
创建日期: 2024.10.10
修改日期：2024.10.10

Copyright (c) 2024 HanKin. All rights reserved.
"""
from werkzeug.utils import secure_filename

filename = secure_filename("example file.txt")
print(filename)  # 输出: example_file.txt

filename = secure_filename("D://example/file.txt")
print(filename)  # 输出: D_example_file.txt

filename = secure_filename("测试.txt")
print(filename)  # 输出: txt