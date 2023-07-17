# -*- coding: utf-8 -*-
"""
文 件 名: delete_line_end_whitespace.py
文件描述: 删除行末空白字符
作    者: HanKin
创建日期: 2023.01.16
修改日期：2023.01.16

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
import stat
import time
  
if __name__ == '__main__':
    """程序入口
    """
    
    # 文件路径，所有方法都会读取到换行符
    FILE_PATH = './sf_redirect.c'
    
    # 1、直接打开就读，速度最快最简洁
    with open(FILE_PATH, 'r', encoding='utf-8') as f:
        for i, line in enumerate(f):
            if line[-1] == ' ':
                print(i)