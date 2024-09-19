# -*- coding: utf-8 -*-
"""
文 件 名: file_operation.py
文件描述: 文件的相关操作
作    者: HanKin
创建日期: 2023.09.28
修改日期：2024.09.05

Copyright (c) 2024 HanKin. All rights reserved.
"""

import os
import time
import shutil

def delete_empty_folder():
    """os.remove函数只能用于删除文件，不能用于删除文件夹
    """

    dir_path = 'path/to/your/empty_directory'
    # 删除空文件夹
    os.rmdir(dir_path)

def delete_file():
    """删除文件
    """
    
    file_path = 'path/to/your/file.txt'
    # 删除文件
    os.remove(file_path)

def delete_folder():
    """如果需要删除非空文件夹，可以使用shutil模块中的shutil.rmtree函数
    """
    
    dir_path = 'path/to/your/non_empty_directory'
    # 删除非空文件夹及其内容
    shutil.rmtree(dir_path)

if __name__ == '__main__':
    file_old_name = 'old_file.txt'
    file_new_name = 'new_file.txt'

    shutil.copy(file_old_name, file_new_name) # 复制一份新文件并重命名
    os.rename(file_new_name, file_old_name)   # 重命名文件
    os.remove(file_old_name)                  # 删除文件