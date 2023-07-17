# -*- coding: utf-8 -*-
"""
文 件 名: draw_love_heart.py
文件描述: 海龟画图： 分红爱心
作    者: HanKin
创建日期: 2023.07.17
修改日期：2023.07.17

Copyright (c) 2023 HanKin. All rights reserved.
"""

import turtle

if __name__ == '__main__':
    """程序入口
    """

    turtle.color('pink')
    turtle.setheading(50)
    turtle.begin_fill()
    turtle.circle(-100, 170)
    turtle.circle(-300, 40)
    turtle.right(38)
    turtle.circle(-300, 40)
    turtle.circle(-100, 170)
    turtle.end_fill()
    turtle.done()