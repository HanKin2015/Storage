# -*- coding: utf-8 -*-
"""
文 件 名: locale_example.py
文件描述: 使用locale获取系统语言
作    者: HanKin
创建日期: 2024.01.02
修改日期：2024.01.02

Copyright (c) 2024 HanKin. All rights reserved.
"""
import locale

if __name__ == '__main__':
    lang, encoding = locale.getdefaultlocale()
    LANGUAGE = lang.split("_")[0]
    print(lang)     # zh_CN
    print(encoding) # cp936
    print(LANGUAGE) # zh