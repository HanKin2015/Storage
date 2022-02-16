# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_copy.py
文件描述: U盘自动拷贝文件
作    者: HanKin
创建日期: 2022.02.15
修改日期：2022.02.15

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import argparse
import logging
import hashlib

def get_file_md5(file_name):
    """获取文件md5值

    通过hashlib库计算文件的md5值
    
    Parameters
    ------------
    file_name : str
        文件名

    Returns
    -------
    str
        返回文件的md5值
    """

    m = hashlib.md5()   #创建md5对象
    with open(file_name,'rb') as fobj:
        while True:
            data = fobj.read(4096)
            if not data:
                break
            m.update(data)  #更新md5对象

    return m.hexdigest()    #返回md5值

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
    source_md5 = get_file_md5('.\\upan_auto_copy.py')
    target_md5 = get_file_md5('.\\test_md5.py')
    if source_md5 != target_md5:
        print('success')
    
    print(get_file_size('.\\upan_auto_copy.py'))
    print(get_file_size('.\\test_md5.py'))
    print(get_file_size('.\\dist\\upan_auto_copy.exe'))

if __name__ == '__main__':
    main()