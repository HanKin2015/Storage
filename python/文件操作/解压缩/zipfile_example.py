# -*- coding: utf-8 -*-
"""
文 件 名: zipfile_example.py
文件描述: zipfile解压zip文件
参    考: https://www.itxm.cn/post/gcche1a7.html
作    者: HanKin
创建日期: 2023.08.11
修改日期：2023.08.11

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
from ftplib import FTP
import time
import zipfile
import shutil

def unzip_file(zipfile_path, file_name, extracted_path):
    # 打开zip文件
    with zipfile.ZipFile(zipfile_path, 'r') as zip_ref:
        # 解压单个文件到指定目录
        zip_ref.extract(file_name, extracted_path)

def unzip_files(zipfile_path, extracted_path):
    if os.path.exists(extracted_path):
        shutil.rmtree(extracted_path)

    # 打开zip文件
    with zipfile.ZipFile(zipfile_path, 'r') as zip_ref:
        # 解压所有文件到指定目录
        #zip_ref.extractall(path=extracted_path, pwd=None, encoding='gbk') 
        for info in zip_ref.infolist(): 
            filename = info.filename.encode('cp437').decode('gbk')
            print(filename)
            zip_ref.extract(info, path=extracted_path, pwd=None) 
            os.rename(os.path.join(extracted_path, info.filename), os.path.join(extracted_path, filename)) 

        print(os.rmdir(os.path.join(extracted_path, zip_ref.infolist()[0].filename)))

def main():
    """主函数
    """
    
    unzip_files('数据.zip', 'path')

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
