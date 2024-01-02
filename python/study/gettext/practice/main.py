# -*- coding: utf-8 -*-
"""
文 件 名: remove_eference_dimension.py
文件描述: 移除引用标注
作    者: HanKin
创建日期: 2023.01.04
修改日期：2023.01.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

from translation import *
import sys

if __name__ == '__main__':
    print(sys.argv)
    if len(sys.argv) == 2:
        if sys.argv[1] == 'zh':
            print('行不通')
    print(HELLO, WORLD, MOTTO)