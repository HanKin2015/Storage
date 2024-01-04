# -*- coding: utf-8 -*-
"""
文 件 名: remove_eference_dimension.py
文件描述: 移除引用标注
作    者: HanKin
创建日期: 2023.01.04
修改日期：2023.01.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

import sys
import translation
if len(sys.argv) == 2:
    translation.load_translation_file(sys.argv[1])
from translation import *
import locale

if __name__ == '__main__':
    lang, encoding = locale.getdefaultlocale()
    LANGUAGE = lang.split("_")[0]
    print(lang, encoding)
    print(HELLO, WORLD, MOTTO)
    print(INCOMPLETE.format("hankin", 29))
    print(INCOMPLETE)
    """
    (base) D:\Github\Storage\python\study\gettext\practice\ultimate>python main.py en
    load_translation_file: os_language en
    zh_CN cp936
    hello world I am I, is not firework
    my name is hankin, and my age is 29.
    my name is {}, and my age is {}.

    (base) D:\Github\Storage\python\study\gettext\practice\ultimate>python main.py zh
    load_translation_file: os_language zh
    zh_CN cp936
    嗨 世界 我就是我，不一样的烟火
    我的名字是hankin，我今年29岁。
    我的名字是{}，我今年{}岁。
    """