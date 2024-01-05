# -*- coding: utf-8 -*-
"""
文 件 名: translation.py
文件描述: 调试动态参数改变翻译语言
作    者: HanKin
创建日期: 2024.01.04
修改日期：2024.01.04

Copyright (c) 2024 HanKin. All rights reserved.
"""
import gettext
import sys
os_language = "zh"
if len(sys.argv) == 2:
    os_language = sys.argv[1]
print("os_language = {}".format(os_language))
localedir = "D:\\Github\\Storage\\python\\study\\gettext\\practice\\locale"
if os_language == "en":
    lang = gettext.translation('practice_en_US', localedir=localedir, languages=['en_US'])
    lang.install('practice_zh_CN')
    _ = lang.gettext
else:
    _ = gettext.gettext

# 翻译字段
HELLO = _("嗨")
WORLD = _("世界")
MOTTO = _("我就是我，不一样的烟火")
INCOMPLETE = _("我的名字是{}，我今年{}岁。")

if __name__ == '__main__':
    print("translation main")