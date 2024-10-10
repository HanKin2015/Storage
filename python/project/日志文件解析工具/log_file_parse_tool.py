# -*- coding: utf-8 -*-
"""
文 件 名: log_file_parse_tool.py
文件描述: 日志文件解析工具
备    注: 
作    者: HanKin
创建日期: 2024.10.08
修改日期：2024.10.08

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
import time
import re
import sys

def unzip_file(file_path):
    """解压文件
    """
    # 取绝对路径最后一个文件名
    file_name = os.path.basename(file_path)
    # 取后缀
    suffix = file_name.split('.')[-1]
    
    if suffix == '.zip':
        print('zip file')
    else:
        print('{} is not zip file'.format(file_name))

def main():
    """主函数
    """
    
    #print(sys.argv)
    argv_cnt = len(sys.argv)
    if argv_cnt != 2:
        print('argument count is not two')
        return

    unzip_file(sys.argv[1])

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

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    os.system("pause")
    
