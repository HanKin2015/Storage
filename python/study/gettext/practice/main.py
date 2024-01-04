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
import locale

if __name__ == '__main__':
    print(sys.argv)
    if len(sys.argv) == 2:
        load_translation_file(sys.argv[1])
        lang, encoding = locale.getdefaultlocale()
        LANGUAGE = lang.split("_")[0]
        print(lang, encoding)
        print(HELLO, WORLD, MOTTO)