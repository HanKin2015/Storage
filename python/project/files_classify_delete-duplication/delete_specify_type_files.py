# -*- coding: utf-8 -*-
"""
文 件 名: delete_specify_type_files.py
文件描述: 删除指定类型的文件
作    者: HanKin
创建日期: 2022.12.15
修改日期：2022.12.15

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import os
import shutil
import random

DIR_PATH = r'D:\Users\Administrator\My Document\WeChat Files\wxid_2gh9d5knc6th21\FileStorage\MsgAttach'
DIR_PATH = r'D:\Github\Storage\python\project\files_classify_delete-duplication\a'
DIR_PATH = r'C:\Users\Administrator\AppData\Local\口袋助理\files'
TMP_PATH = r'D:\hj'

def get_dir_file_types(path):
    '''获取目录下拥有的文件类型，即文件后缀
    os.walk函数会自动遍历当前目录及子目录
    递归顺序是先当前目录，然后再递归第一个子目录，再递归子子目录，会将第一个目录插入遍历队列中
    '''

    file_types = []
    for root, dirs, files in os.walk(path):
        for dir in dirs:
            dir_path = os.path.join(root, dir)
            # 判断是否为空文件夹
            #if not os.listdir(dir_path):
                #print(dir_path)
                #os.rmdir(dir_path)
        for file in files:
            file_path = os.path.join(root, file)
            #print(file_path)
            suffix = os.path.splitext(file_path)[-1]
            file_types.append(suffix)
    
    file_types = set(file_types)
    print('there are {} file types'.format(len(file_types)))
    #print(file_types)
    
    for suffix in file_types:
        if len(suffix) <= 10:
            print(suffix)

def delete_empty_dirs():
    """删除空的文件夹
    """
    
    delete_dirs_cnt = 0
    for root, dirs, files in os.walk(DIR_PATH):
        for dir in dirs:
            dir_path = os.path.join(root, dir)
            if not os.listdir(dir_path):
                #print(dir_path)
                os.rmdir(dir_path)
                delete_dirs_cnt += 1
    print('there are {} empty dirs which are deleted'.format(delete_dirs_cnt))

def delete_specify_type_files(path):
    """删除指定类型的文件
    后缀名长度大于10的，目前看见最长的比较正常的是.patch
    
    """
    
    delete_files_cnt = 0
    specify_types = ['.log', '.dat', '.rst', '.cpm', '.deb', '.wxtmp', '.gz', '.cd', '.clog']
    for root, dirs, files in os.walk(path):
        for file in files:
            file_path = os.path.join(root, file)
            #print(file_path)
            suffix = os.path.splitext(file_path)[-1]
            
            # 删除后缀名长度过长的
            if len(suffix) > 10:
                os.remove(file_path)
                delete_files_cnt += 1
            # 删除后缀名长度为0的
            if len(suffix) == 0:
                #print(file_path)
                os.remove(file_path)
                delete_files_cnt += 1
            # 删除指定后缀名的（不排除的原因怕有没有记录到的格式被删除）
            if suffix in specify_types:
                os.remove(file_path)
                delete_files_cnt += 1
            # 删除末尾两个都是数字的
            if suffix[-1].isdigit() and suffix[-2].isdigit():
                os.remove(file_path)
                delete_files_cnt += 1
    print('there are {} files which are deleted'.format(delete_files_cnt))

def move_files_to_specify_dir(path):
    """移动文件到指定文件夹
    """

    for root, dirs, files in os.walk(path):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                shutil.move(file_path, TMP_PATH)
            except Exception as err:
                print(err)
                # 同名文件
                random_num = random.randint(1, 100)
                new_file_path = file_path + str(random_num)
                #print(new_file_path)
                os.rename(file_path, new_file_path)
                shutil.move(new_file_path, TMP_PATH)
                
def main():
    """主函数
    """
    
    #move_files_to_specify_dir(DIR_PATH)
    delete_specify_type_files(TMP_PATH)
    get_dir_file_types(TMP_PATH)
    for i in range(5):
        delete_empty_dirs()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))