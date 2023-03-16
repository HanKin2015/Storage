# -*- coding: utf-8 -*-
"""
文 件 名: pynput_example.py
文件描述: pynput是监听、操控鼠标和键盘的跨平台第三方python库
备    注: https://www.cnblogs.com/tobe-goodlearner/p/tutorial-pynput.html
          暂时没有这个需求，有inpuhook就可以了
作    者: HanKin
创建日期: 2023.03.14
修改日期：2023.03.14
Copyright (c) 2023 HanKin. All rights reserved.
"""

import pynput, time

def on_move(x, y):
    print('Pointer moved to {0}'.format((x, y)))

def on_click(x, y, button, pressed):
    print('{0} at {1}'.format(
        'Pressed' if pressed else 'Released',
        (x, y)))
    if not pressed:
        # Stop listener
        return False

def on_scroll(x, y, dx, dy):
    print('Scrolled {0} at {1}'.format(
        'down' if dy < 0 else 'up',
        (x, y)))

# Collect events until released
with pynput.mouse.Listener(
        on_move=on_move,
        on_click=on_click,
        on_scroll=on_scroll) as listener:
    listener.join()
