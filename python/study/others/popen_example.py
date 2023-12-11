# -*- coding: utf-8 -*-
"""
文 件 名: popen_example.py
文件描述: 通过popen函数执行dos命令
作    者: HanKin
创建日期: 2023.09.04
修改日期：2023.09.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import os
import sys

def get_port_status():
    """
    获取端口状态
    :return: 直接返回查询结果
    """
    
    # 完全匹配40001端口
    find_port = 'netstat -aon|findstr :40001'
    p = os.popen(find_port, 'r')
    text = p.readlines()
    p.close()
    if text:
        for task in text[:]:
            if task.strip()[-1] == '0' or 'LISTENING' not in task.strip():
                text.remove(task)
    return text

def directory_has_space():
    """
    Windows执行命令时需要注意文件夹为空的情况
    """
    
    exe_file_path = r"D:\Users\User\Desktop\ttt 1\device_helper.exe"
    result_file_path = r"D:\Users\User\Desktop\ttt 1\aa"
    extra_info_file_path = r"D:\Users\User\Desktop\ttt 1\bb"
    #exe_file_path = exe_file_path.replace(" ", "\ ")           # 不行
    #result_file_path = result_file_path.replace(" ", "\\ ")    # 不行
    #extra_info_file_path = extra_info_file_path.replace(" ", "\\ ")
    #cmd = r"'{}' -p '{}' '{}'".format(exe_file_path, result_file_path, extra_info_file_path)   # 不行
    cmd = r'"{}" -p "{}" "{}"'.format(exe_file_path, result_file_path, extra_info_file_path)    # 正解
    os.popen(cmd)
    #if os.path.exists('"{}"'.format(result_file_path)):
    if os.path.exists(result_file_path):    # python自己的库会自己处理文件夹空格
        print("ok")
    else:
        print("no")

def main():
    """主函数
    """
    
    print(get_port_status())
    
    if len(sys.argv) == 1:
        print(sys.argv)
    elif len(sys.argv) == 2:
        if sys.argv[1] == "--help":
            print("usage: popen_example.pyw [option]")
            print("options:")
            print("[parameter-free]: launch Tools")
            print("epoch: launch Tools about Epoch(Back-end services only)")
        else:
            print("invalid option")
            print("Try 'popen_example.pyw --help' for more information")
    else:
        print("invalid option")
        print("Try 'popen_example.pyw --help' for more information")

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))