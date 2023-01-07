# -*- coding: utf-8 -*-
"""
文 件 名: remove_eference_dimension.py
文件描述: 移除引用标注
作    者: HanKin
创建日期: 2023.01.04
修改日期：2023.01.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

def remove_eference_dimension(file_path):
    """移除引用标注
    """
    
    with open(file_path, 'r') as f:
        for line in f:
            print(line)

def main():
    """主函数
    """
    
    file_path = 'D:\Github\GitBook\gitbook\Entertainment\television.md'
    remove_eference_dimension(file_path)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))