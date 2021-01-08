# -*- coding: utf-8 -*-
"""
Created on Sat Nov 21 12:04:41 2020

@author: hankin
"""

import os
import time
import math
import sys

# 增加libary库的搜索路径
sys.path.append('../../libary/')
import md5

def main(root_dir): 
    list_dirs = os.walk(root_dir)
    index = 0
    sum_dirs = 0
    sum_files = 0
    for root, dirs, files in list_dirs:
        print('{}: current {} dir has {} dirs, has {} files.'.format(index, root, len(dirs), len(files)))
        index += 1
        sum_dirs += len(dirs)
        sum_files += len(files)
        
        # 注意，这里使用lambda表达式，将文件按照最后修改时间顺序升序排列
        # os.path.getmtime() 函数是获取文件最后修改时间
        # os.path.getctime() 函数是获取文件最后创建时间
        files = sorted(files, key=lambda x: os.path.getmtime(os.path.join(root, x)))
        
        # 文件md5值列表
        files_md5_list = []
        # 待删除的文件列表(重复)
        delete_files_list = []
        
        file_index = 1
        sum_file = len(files)
        
        for file in files:
            file_absolute_path = root + '/' + file
            print('{}/{}: {}  {}  {}KB'.format(file_index, sum_file, file, time.strftime('%Y/%m/%d %H:%M', time.localtime(os.path.getctime(file_absolute_path))), math.ceil(os.path.getsize(file_absolute_path)/1024)))
            file_index += 1
            
            file_md5 = md5.get_file_md5(file_absolute_path)
            #print('md5 = {}'.format(file_md5))
            if file_md5 in files_md5_list:
                delete_files_list.append(file_absolute_path)
            else:
                files_md5_list.append(file_md5)
        
        print('There are {} files which will be deleted.'.format(len(delete_files_list)))
        for idx, file in enumerate(delete_files_list):
            print('{}: delete {} file.'.format(idx+1, file))
            os.remove(file)
         
    print('dirs sum is {}, files sum is {}.'.format(sum_dirs, sum_files))

if __name__=="__main__":
    #root_dir = 'D:/Github/Storage/python/project/'
    root_dir = 'D:/Users/Administrator/My Document/WeChat Files/wxid_2gh9d5knc6th21/FileStorage/File'
    main(root_dir)



