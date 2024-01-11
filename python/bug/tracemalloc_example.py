# -*- coding: utf-8 -*-
"""
文 件 名: tracemalloc_example.py
文件描述: tracemalloc追踪内存使用情况
备    注: tracemalloc和win32com.client两者存在兼容性问题
作    者: HanKin
创建日期: 2024.01.09
修改日期：2024.01.09

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
import win32com.client
import pythoncom
import tracemalloc

def get_udev_info_list():

    #pythoncom.CoInitialize()
    wmi = win32com.client.GetObject("winmgmts:")
    #del wmi
    #pythoncom.CoUninitialize()
    print(1)

if __name__ == '__main__':
    """程序入口
    """
    
    print('******** starting ********')
    start_time = time.time()

    # 开始跟踪内存分配
    tracemalloc.start()

    for i in range(1000):
        get_udev_info_list()
        time.sleep(1)

        # 每次循环后，打印内存分配情况
        current, peak = tracemalloc.get_traced_memory()
        print(f"Current memory usage is {current / 10**6}MB; Peak was {peak / 10**6}MB")

    # 停止跟踪内存分配
    tracemalloc.stop()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
