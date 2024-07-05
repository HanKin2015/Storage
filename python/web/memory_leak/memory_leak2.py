# -*- coding: utf-8 -*-
"""
文 件 名: memory_leak2.py
文件描述: 构建内存泄露
备    注: 
作    者: HanKin
创建日期: 2024.06.28
修改日期：2024.06.28

Copyright (c) 2024 HanKin. All rights reserved.
"""
import json
import requests

def upload_total():
    """测试分析平台服务器，上传工具使用次数
    """
    version_list = []
    version_list2 = []
    for i in range(10):
        version_list.append([i]*1000)
        version_list2 = version_list
    return version_list2

def memory_usage_psutil():
    # return the memory usage in MB
    import psutil,os
    process = psutil.Process(os.getpid())
    mem = process.memory_info()[0] / float(2 ** 20)
    return mem
    
if __name__ == '__main__':
    for i in range(10000):
        upload_total()
        if(i%100==0):
            print(memory_usage_psutil())