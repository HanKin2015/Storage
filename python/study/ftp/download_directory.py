# -*- coding: utf-8 -*-
"""
文 件 名: download_directory.py
文件描述: 从ftp服务器下载文件夹
作    者: HanKin
创建日期: 2023.08.10
修改日期：2023.08.10

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
from ftplib import FTP
import time

def download_folder(ftp, folder_path, local_path):
    # 切换到目标文件夹
    ftp.cwd(folder_path)

    # 创建本地文件夹
    os.makedirs(local_path, exist_ok=True)

    # 获取文件夹中的文件和子文件夹
    files = ftp.nlst()
    print(files)

    # 下载文件
    for file in files:
        local_file = os.path.join(local_path, file)
        if '.' in file:  # 如果是文件
            with open(local_file, 'wb') as f:
                ftp.retrbinary('RETR ' + file, f.write)
        else:  # 如果是文件夹
            print(local_file, ftp.nlst(file))
            download_folder(ftp, file, local_file)

def main():
    """主函数
    """
    
    # 连接 FTP 服务器
    ftp = FTP('xx.xx.xx.xxx')
    ftp.login(user='xx', passwd='xx')

    # 获取目录列表
    directory = ftp.nlst('/')
    #print(directory)

    # 下载文件夹
    path = u'/G://ywt//YWTDB//代码模块//U盘映射加速'
    # 使用.encode('latin-1', 'ignore').decode('latin-1')是不行的，最终会变成/G:/ywt/YWTDB/U/fat
    download_folder(ftp, path.encode(encoding='gbk').decode(encoding='latin-1'), 'path')

    # 关闭 FTP 连接
    ftp.quit()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
