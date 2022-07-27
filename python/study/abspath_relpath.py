# -*- coding: utf-8 -*-
"""
文 件 名: abspath_relpath.py
文件描述: 跨平台相对路径和绝对路径
作    者: HanKin
创建日期: 2022.07.21
修改日期：2022.07.21

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import sys

# 是否为Windows系统
is_windows = False
if sys.platform == 'win32' or sys.platform == 'win64':
    is_windows = True

def main():
    print('is_windows: {}'.format(is_windows))
    
    if is_windows:
        open('D:\Github\Storage\python\study\short_url\generate_short_url.py')
        open('D:\\Github\\Storage\\python\\study\\short_url\\generate_short_url.py')
        open('D:/Github/Storage/python/study/short_url/generate_short_url.py')
        open('.\short_url\generate_short_url.py')
        open('.\\short_url\\generate_short_url.py')
        open('./short_url/generate_short_url.py')
    else:
        open('/media/sangfor/vdb/boost/hello_boost.cpp')
        open('./boost/hello_boost.cpp')
        
        # IOError: [Errno 2] No such file or directory: '\\media\\sangfor\\vdb\\boost\\hello_boost.cpp'
        open('\\media\\sangfor\\vdb\\boost\\hello_boost.cpp')
        # IOError: [Errno 2] No such file or directory: '.\x08oost\\hello_boost.cpp'
        open('.\boost\hello_boost.cpp')
        # IOError: [Errno 2] No such file or directory: '.\\boost\\hello_boost.cpp'
        open('.\\boost\\hello_boost.cpp')
        # IOError: [Errno 2] No such file or directory: '\\\\media\\\\sangfor\\\\vdb\\\\boost\\\\hello_boost.cpp'
        open(r'\\media\\sangfor\\vdb\\boost\\hello_boost.cpp')
        # IOError: [Errno 2] No such file or directory: '.\\boost\\hello_boost.cpp'
        open(r'.\boost\hello_boost.cpp')
        # IOError: [Errno 2] No such file or directory: '.\\\\boost\\\\hello_boost.cpp'
        open(r'.\\boost\\hello_boost.cpp')
    
    path1 = os.path.abspath('.')   #表示当前所处的文件夹的绝对路径
    path2 = os.path.abspath('..')  #表示当前所处的文件夹上一级文件夹的绝对路径
    print(path1)
    print(path2)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))




