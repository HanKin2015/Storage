# -*- coding: utf-8 -*-
"""
文 件 名: max_file_size.py
文件描述: 计算每个文件夹大小，文件最大值、最小值
作    者: HanKin
创建日期: 2023.02.21
修改日期：2023.02.21

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import re
import os

# 过滤的文件夹
FILTER_DIRS = ['.git', 'gitbook', 'Styles', 'Source']

def get_file_size(file_path):
    """获取文件的大小

    结果保留两位小数，单位为KB
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的大小
    """

    file_size = os.path.getsize(file_path)
    file_size = file_size / float(1024)
    return round(file_size, 2)

def main():
    """主函数
    """

    dir_path = 'D:\\Github\\GitBook\\master'
    dir_count = 0
    file_count = 0
    max_file = {'file_path': '', 'file_size': -1}
    min_file = {'file_path': '', 'file_size': 100}
    dir_size = 0
    for root, dirs, files in os.walk(dir_path):
        if root.count('\\') != 4:
            #print('this is a multistage directory [{}], filter out'.format(root))
            continue
        if root.split('\\')[-1] in FILTER_DIRS:
            #print('this is a special filter directory [{}], filter out'.format(root))
            continue
        #print(root)
        dir_count += 1

        root_size = 0
        for file in files:
            file_path = root + '\\' + file
            #print(file_path)
            file_count += 1
            file_size = get_file_size(file_path)
            root_size += file_size
            if file_size > max_file['file_size']:
                max_file['file_path'] = file_path
                max_file['file_size'] = file_size
            if file_size < min_file['file_size']:
                min_file['file_path'] = file_path
                min_file['file_size'] = file_size
        dir_size += root_size
        print('{} directory is {:.2f} KB'.format(root, root_size))
    print('dir_count = {}, file_count = {}, dir_size = {:.2f} KB'.format(dir_count, file_count, dir_size))
    print(max_file)
    print(min_file)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))