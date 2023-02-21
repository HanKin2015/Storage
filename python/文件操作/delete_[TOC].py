# -*- coding: utf-8 -*-
"""
文 件 名: delete_[TOC].py
文件描述: 删除md文件第一行的[TOC]字样
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

def delete_toc(file_path):
    """删除md文件第一行的[TOC]字样
    """

    with open(file_path, 'r', encoding = 'utf-8') as f:
        lines = f.readlines()
        #print('{} have {} lines'.format(file_path, len(lines)))
        
        # 空文件
        if len(lines) == 0:
            print('{} is a null markdown***************'.format(file_path))
            return 0
        
        # 不存在[TOC]字样
        if '[TOC]' not in lines[0]:
            return 0
    
    print('{} have [TOC] words'.format(file_path))
    
    # 删除第一行
    with open(file_path, 'w', encoding = 'utf-8') as f:
        for line in lines[1:]:
            f.write(line)
    return 1

def main():
    """主函数
    """

    dir_path = 'D:\\Github\\GitBook\\gitbook'
    dir_count = 0
    file_count = 0
    toc_count = 0
    for root, dirs, files in os.walk(dir_path):
        if root.count('\\') != 4:
            #print('this is a multistage directory [{}], filter out'.format(root))
            continue
        if root.split('\\')[-1] in FILTER_DIRS:
            #print('this is a special filter directory [{}], filter out'.format(root))
            continue
        #print(root)
        dir_count += 1

        for file in files:
            file_path = root + '\\' + file
            #print(file_path)
            file_count += 1
            ret = delete_toc(file_path)
            toc_count += ret
    print('dir_count = {}, file_count = {}, toc_count = {}'.format(dir_count, file_count, toc_count))

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))