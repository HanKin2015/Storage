# -*- coding: utf-8 -*-
"""
文 件 名: pyautogui_example2.py
文件描述: 模拟鼠标点击
备    注: 
作    者: HanKin
创建日期: 2024.11.21
修改日期：2024.11.21

Copyright (c) 2024 HanKin. All rights reserved.
"""
import pyautogui
import time

# 等待 5 秒，以便你可以切换到目标窗口
time.sleep(5)

# 获取当前鼠标位置
current_mouse_x, current_mouse_y = pyautogui.position()
print(f"当前鼠标位置: ({current_mouse_x}, {current_mouse_y})")

# 模拟鼠标点击
pyautogui.click()  # 在当前鼠标位置点击

# 或者指定位置点击
# pyautogui.click(x=100, y=200)  # 在 (100, 200) 位置点击

# 模拟右键点击
# pyautogui.rightClick()

# 模拟双击
# pyautogui.doubleClick()

# 模拟移动鼠标并点击
# pyautogui.moveTo(100, 200, duration=1)  # 移动到 (100, 200) 位置，持续 1 秒
# pyautogui.click()
