# -*- coding: utf-8 -*-
"""
文 件 名: read_udev_insert_info.py
文件描述: 从内核文件中读取插入的usb设备信息
备    注: 
作    者: HanKin
创建日期: 2024.05.21
修改日期：2024.05.21

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
def remove_empty_folders(directory_path):
    for root, dirs, files in os.walk(directory_path, topdown=False):
        for folder in dirs:
            folder_path = os.path.join(root, folder)
            if not os.listdir(folder_path):
                os.rmdir(folder_path)

# 用Python脚本重命名目录中的多个文件
def rename_files(directory_path, old_name, new_name):
    for filename in os.listdir(directory_path):
        if old_name in filename:
            new_filename = filename.replace(old_name, new_name)
            os.rename(os.path.join(directory_path, filename),
                      os.path.join(directory_path, new_filename))



