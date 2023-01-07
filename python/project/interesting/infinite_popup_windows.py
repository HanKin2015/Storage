# -*- coding: utf-8 -*-
"""
文 件 名: infinite_popup_windows.py
文件描述: 无限弹窗
作    者: HanKin
创建日期: 2022.12.29
修改日期：2022.12.29

Copyright (c) 2022 HanKin. All rights reserved.
"""
import time
import os

def infinite_popup_windows():
    """无限弹窗
    """
    
    while True:
        os.system('start cmd')
        time.sleep(5)

def clear_windows():
    """清理窗口，会把自己的执行窗口也清理
    """
    
    os.system('start taskkill /f /im cmd.exe /t')

def main():
    #infinite_popup_windows()
    clear_windows()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

