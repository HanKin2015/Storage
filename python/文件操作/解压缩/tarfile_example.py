# -*- coding: utf-8 -*-
"""
文 件 名: tarfile_example.py
文件描述: tarfile解压tar文件
参    考: 
作    者: HanKin
创建日期: 2024.01.11
修改日期：2024.01.11

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
import r=tarfile

def extract_tar(file_path, target_dir):
    with tarfile.open(file_path, 'r') as tar:
        tar.extractall(path=target_dir)

def extract_tar(file_path, target_dir):
    with tarfile.open(file_path, 'r') as tar:
        for member in tar.getmembers():
            tar.extract(member, path=target_dir)

def main():
    """主函数
    """
    
    extract_tar('archive.tar', 'target_folder')

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
