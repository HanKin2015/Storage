# -*- coding: utf-8 -*-
"""
文 件 名: translation0.py
文件描述: 原始可用版本
作    者: HanKin
创建日期: 2024.01.02
修改日期：2024.01.02

Copyright (c) 2024 HanKin. All rights reserved.
"""
import gettext
import locale

localedir = "D:\\Github\\Storage\\python\\study\\gettext\\practice\\locale"
lang, encoding = locale.getdefaultlocale()
os_language = lang.split("_")[0]

# 加载翻译文件（practice必须要和mo文件名一样）
print("load_translation_file: os_language {}".format(os_language))
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
