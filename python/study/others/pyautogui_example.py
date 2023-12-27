# -*- coding: utf-8 -*-
"""
文 件 名: pyautogui_example.py
文件描述: 学习使用pyautogui库截图
作    者: HanKin
创建日期: 2023.12.21
修改日期：2023.12.21

Copyright (c) 2023 HanKin. All rights reserved.
"""
import pyautogui
import datetime
import os

if not os.path.exists('./img/screenshot'):
    os.makedirs('./img/screenshot')

now_time = datetime.datetime.now()
img_name_prefix = '{}-{}-{}_{}-{}-{}'.format(now_time.year, now_time.month, now_time.day,
                                             now_time.hour, now_time.minute, now_time.second)
for idx in range(4):
    img_name = '{}_{}.png'.format(img_name_prefix, idx)
    img_path = os.path.join('img', 'screenshot', img_name)
    exec('img_path{} = {}'.format(idx, repr(img_path)))
    exec('print(img_path{})'.format(idx))

# 截图
img = pyautogui.screenshot()
img = pyautogui.screenshot(img_path0)

# 指定截图区域
img = pyautogui.screenshot(region=(100, 100, 200, 200))
img.save(img_path1)

img = pyautogui.screenshot(img_path2, region=(100, 100, 200, 200))  # 方式一（推荐）
img = pyautogui.screenshot(img_path3, region=[100, 100, 200, 200])  # 方式二
print(img)  # <PIL.Image.Image image mode=RGB size=200x200 at 0x25BA160>