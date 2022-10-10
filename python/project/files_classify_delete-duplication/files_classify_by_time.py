# -*- coding: utf-8 -*-
"""
文 件 名: files_classify_by_time.py
文件描述: 按创建时间进行分类文件和文件夹
作    者: HanKin
创建日期: 2022.09.29
修改日期：2022.09.29

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import os
import shutil

DIR_PATH = r'C:\Users\Administrator\AppData\Local\口袋助理\files'

def test():
    '''os.walk递归遍历
    '''

    for root, dirs, files in os.walk(DIR_PATH):
        for dir in dirs:
            path = os.path.join(root, dir)
            print(path)
        for file in files:
            path = os.path.join(root, file)
            #print(path)

def main():
    for name in os.listdir(DIR_PATH):
        path = os.path.join(DIR_PATH, name)
        create_time = os.path.getctime(path)
        dir_name = time.strftime('%Y-%m-%d', time.localtime(create_time))
        dir_path = os.path.join(DIR_PATH, dir_name)
        if not os.path.exists(dir_path):
            os.makedirs(dir_path)
            try:
                shutil.move(path, dir_path)
            except Exception as err:    # 异常处理很重要
                print(err)
        else:
            try:
                shutil.move(path, dir_path)
            except Exception as err:
                print(err)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))