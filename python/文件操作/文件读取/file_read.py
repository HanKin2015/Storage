# -*- coding: utf-8 -*-
"""
文 件 名: file_read.py
文件描述: 文件读取
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
    FILE_PATH = './data.txt'
    
    # 1、直接打开就读，速度最快最简洁
    with open(FILE_PATH, 'r', encoding='utf-8') as f:
        for line in f:
            print(line)
            print('一行数据')
            break
            
    # 2、用read()打开，把文件全部内容一次性读到一个字符串中，ff是字符串，本质上是tuple
    with open(FILE_PATH, 'r', encoding='utf-8') as f:
        ff = f.read()
        print(ff)

    # 3、用readlines()，将文件所用内容以行为区分读到一个列表中 ，列表中的每一个元素是一行
    with open(FILE_PATH, 'r', encoding='utf-8') as f:
        lines = f.readlines()
        for line in lines:
            print(line)
            break
            
    # 4、用readline()，一行一行的读，非常的省内存，当文件巨大的情况下是有好处的
    with open(FILE_PATH, 'r', encoding='utf-8') as f:
        line = f.readline()
        while line:
            print(line)
            line=f.readline()
            break
