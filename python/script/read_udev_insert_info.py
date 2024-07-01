# -*- coding: utf-8 -*-
"""
文 件 名: read_udev_insert_info.py
文件描述: 从内核文件中读取插入的usb设备信息
备    注: 
作    者: HanKin
创建日期: 2024.06.13
修改日期：2024.06.13

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os


def list_specified_suffix_files(dir_path, suffix):
    for root, dirs, files in os.walk(dir_path, topdown=False):
        for file in files:
            # 处理文件
            if file.split(".")[-1] == suffix:
                print("current suffix[{}] file: {}".format(suffix, file))
                file_path = os.path.join(root, file)
                



if __name__ == '__main__':
    directory_path = r'D:\Users\Administrator\My Document\WXWork\1688854308416542\Cache\File\2024-05'
    list_specified_suffix_files(directory_path, 'zip')
