# -*- coding: utf-8 -*-
"""
文 件 名: file_name_cannot_colon.py
文件描述: 文件名不能包含冒号，但是可以有空格
作    者: HanKin
创建日期: 2023.12.22
修改日期：2023.12.22

Copyright (c) 2023 HanKin. All rights reserved.
"""
with open("a b.txt", "w") as f:
    f.write("hello")

with open("a:b.txt", "w") as f:
    f.write("hello")    # FileNotFoundError: [Errno 2] No such file or directory: 'a:b.txt'