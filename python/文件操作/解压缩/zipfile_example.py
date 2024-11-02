# -*- coding: utf-8 -*-
"""
文 件 名: zipfile_example.py
文件描述: zipfile解压zip文件
参    考: https://www.itxm.cn/post/gcche1a7.html
作    者: HanKin
创建日期: 2023.08.11
修改日期：2024.11.01

Copyright (c) 2024 HanKin. All rights reserved.
"""

import os
from ftplib import FTP
import time
import zipfile
import shutil

def unzip_file(zipfile_path, file_name, extract_path):
    """解压单个文件到指定目录
    注意该文件只能在第一层目录中，不能在子目录中，否则会抛出异常
    """
    if not os.path.exists(extract_path):
        os.makedirs(extract_path)

    # 打开zip文件
    with zipfile.ZipFile(zipfile_path, 'r') as zip_ref:
        try:
            # 解压单个文件到指定目录
            zip_ref.extract(file_name, extract_path)
        except Exception as err:
            print(err)

def unzip_files(zipfile_path, extract_path):
    """全部解压缩（标准教程）
    """
    if os.path.exists(extract_path):
        shutil.rmtree(extract_path)

    # 打开zip文件
    with zipfile.ZipFile(zipfile_path, 'r') as zip_ref:
        # 解压所有文件到指定目录
        #zip_ref.extractall(path=extract_path, pwd=None, encoding='gbk') 
        for info in zip_ref.infolist(): 
            # 检查文件名是否为空(不检查会有问题)
            if not info.filename:
                print('Warning: Found a info with an empty filename, skipping.')
                continue
            
            """出现中文乱码了
            # 确保目标路径存在
            target_path = os.path.join(extract_path, info.filename)
            if info.is_dir():
                os.makedirs(target_path, exist_ok=True)
            else:
                # 确保父目录存在
                os.makedirs(os.path.dirname(target_path), exist_ok=True)
                with zip_ref.open(info) as source, open(target_path, 'wb') as target:
                    target.write(source.read())
            """

            filename = info.filename.encode('cp437').decode('gbk')
            print(''.format(filename))
            zip_ref.extract(info, path=extract_path, pwd=None) 
            os.rename(os.path.join(extract_path, info.filename), os.path.join(extract_path, filename)) 

def main():
    """主函数
    """
    
    #unzip_file('解压缩.zip', 'a.txt', 'extract_path')
    unzip_files('解压缩.zip', 'extract_path')

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
