# -*- coding: utf-8 -*-
"""
文 件 名: infinite_lock_windows.py
文件描述: 无限锁屏
作    者: HanKin
创建日期: 2022.12.29
修改日期：2022.12.29

Copyright (c) 2022 HanKin. All rights reserved.
"""
import time
import ctypes

def infinite_lock_windows():
    """无限锁屏
    """
    
    while True:
        user = ctypes.windll.LoadLibrary("user32.dll")
        user.LockWorkStation()
        time.sleep(30)
        infinite_lock_windows()

def main():
    infinite_lock_windows()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

