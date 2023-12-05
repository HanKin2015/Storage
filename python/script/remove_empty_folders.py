# -*- coding: utf-8 -*-
"""
文 件 名: remove_empty_folders.py
文件描述: 用Python脚本删除目录中的空文件夹
备    注: https://mp.weixin.qq.com/s/HUPCOCCens6XpxKHNPD-Yw
作    者: HanKin
创建日期: 2021.12.05
修改日期：2023.12.05

Copyright (c) 2023 HanKin. All rights reserved.
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



