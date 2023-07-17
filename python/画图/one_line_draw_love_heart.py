# -*- coding: utf-8 -*-
"""
文 件 名: one_line_draw_love_heart.py
文件描述: 一行代码： 文字效果爱心
备    注: https://mp.weixin.qq.com/s/F-etmcHj5AKJRNLW2unQEg
作    者: HanKin
创建日期: 2023.07.17
修改日期：2023.07.17

Copyright (c) 2023 HanKin. All rights reserved.
"""

print('\n'.join([''.join([('Love'[(x-y) % len('Love')] if ((x*0.05)**2+(y*0.1)**2-1)**3-(x*0.05)**2*(y*0.1)**3 <= 0else' ') for x in range(-30, 30)]) for y in range(30, -30, -1)]))