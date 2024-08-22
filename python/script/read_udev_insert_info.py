# -*- coding: utf-8 -*-
"""
文 件 名: read_udev_insert_info.py
文件描述: 从内核文件中读取插入的usb设备信息
备    注: 
作    者: HanKin
创建日期: 2024.06.13
修改日期：2024.08.06

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
import time

def list_specified_suffix_files(dir_path, suffix_list):
    """
    列出指定后缀的文件
    """
    count = 0
    for root, dirs, files in os.walk(dir_path, topdown=False):
        for file in files:
            suffix = file.split(".")[-1]
            if suffix in suffix_list:
                print("current suffix[{}] file: {}".format(suffix, file))
                count += 1
                file_path = os.path.join(root, file)
    print("there are {} files with {} suffix".format(count, suffix_list))

def read_udev_info_from_linux_box():
    system_log_path = r"D:\Users\Administrator\My Document\WXWork\1688854308416542\Cache\File\2024-08\20230341_10.191.100.27_5.9.1.683_7BP3460135\var\log\system.log"
    with open(system_log_path, "r", encoding="utf-8") as f:
        for line in f:
            if "New USB device found" in line:
                print(line)

def read_udev_info_from_android_box():
    pass

def main():
    """主函数
    """

def debug():
    """调试
    """
    directory_path = r'D:\Users\Administrator\My Document\WXWork\1688854308416542\Cache\File\2024-05'
    #directory_path = r'D:\Users\Administrator\Desktop'
    #list_specified_suffix_files(directory_path, ['docx', 'doc'])
    read_udev_info_from_linux_box()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    #main()
    debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    
