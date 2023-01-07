# -*- coding: utf-8 -*-
"""
文 件 名: modify_desktop_wallpaper.py
文件描述: 修改电脑桌面壁纸
备    注：脚本运行后，注册表的值并没有变化，但是壁纸变了，并且不使用win7系统
作    者: HanKin
创建日期: 2022.12.29
修改日期：2022.12.29

Copyright (c) 2022 HanKin. All rights reserved.
"""

import win32api     # 调用Windows底层的接口配置   pip install pywin32
import win32con     # 修改数据
import win32gui     # 提交对应的数据
import os           # Python 管理文件工具包
import random       # 取出对应的随机值
import time         # 时间管理模块

def set_wallpaper():
    path = os.listdir(r'C:\Users\Administrator\Downloads\picture')
    for i in path:
        print(i)
        img_path = r'C:\Users\Administrator\Downloads\picture' + '\\' + i
        print(img_path)
        # 打开注册表  句柄
        k = win32api.RegOpenKeyEx(win32con.HKEY_CURRENT_USER, 'Control Panel\Desktop', 0, win32con.KEY_SET_VALUE)
        print(k)
        # 2 拉伸壁纸  0 壁纸居中  6 适应 10 填充
        win32api.RegSetValueEx(k, "WallpaperStyle", 0, win32con.REG_SZ, '2')
        win32gui.SystemParametersInfo(win32con.SPI_SETDESKWALLPAPER, img_path, win32con.SPIF_SENDWININICHANGE)
        time.sleep(10)

def main():
    set_wallpaper()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
