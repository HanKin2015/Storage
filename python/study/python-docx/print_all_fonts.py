# -*- coding: utf-8 -*-
"""
文 件 名: print_all_fonts.py
文件描述: 打印出所有安装的字体
备    注：但是没有打印出中文字体
作    者: HanKin
创建日期: 2023.09.15
修改日期：2023.09.15
Copyright (c) 2023 HanKin. All rights reserved.
"""
import matplotlib.font_manager as fm
fonts = fm.findSystemFonts()
for font in fonts:
    print(font)