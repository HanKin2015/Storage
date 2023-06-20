# -*- coding: utf-8 -*-
"""
文 件 名: usb_autorun.py
文件描述: 细思恐极，插上U盘就开始执行Python代码拷贝U盘中的资料
作    者: HanKin
创建日期: 2022.09.01
修改日期：2022.09.01

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import os
import shutil
import re

def traverse_directories():
    for root, dirs, files in os.walk('/media/hankin/', topdown=False):
        print('----', root)
        for name in files:
            file_path = os.path.join(root, name)
            print(file_path)
            print(time.ctime(os.path.getctime(file_path)))
            shutil.copy2(file_path, '/media/test/')
        for name in dirs:
            print(os.path.join(root, name))

def detect_upan():
    usb_path = '/media/'
    content = os.listdir(usb_path)
    while True:
        new_content = os.listdir(usb_path)
        if new_content != content:
            print('new_content: {}\ncontent: {}'.format(new_content, content))
            break
        time.sleep(3)
    
    x = [item for item in new_content if item not in content]
    print(x)
    print(x[0])
    
    # 首先只会有一个U盘插入，所以取x[0]
    # 其次copytree只拷贝文件夹，目标文件夹未创建
    #shutil.copytree(os.path.join(usb_path, x[0]), '/media/hankin/')
    for root, dirs, files in os.walk(os.path.join(usb_path, x[0]), topdown=False):
        for name in files:
            file_path = os.path.join(root, name)
            # 选择文件大小小于3M并且指定文件后缀
            regex_filename = re.compile('(.*zip$)|(.*rar$)|(.*docx$)|(.*ppt$)|(.*xls$)')
            if os.path.getsize(file_path) < 3*1024*1024 and regex_filename.match(file_path):
                shutil.copy2(os.path.join(root, name), '/media/test/')

def convert_bytes(num):
    for x in ['bytes', 'KB', 'MB', 'GB', 'TB']:
        if num < 1024.0:
            return "%3.1f %s" % (num, x)
        num /= 1024.0

def get_file_size(file_path):
    try:
        file_size = os.path.getsize(file_path)
        return file_size
    except Exception as err:
        print(err)

def main():
    #detect_upan()
    traverse_directories()
    print(convert_bytes(get_file_size('/media/sangfor/vdb/study/hj/custom-built_cti-support-20220729120205-Q2022071902402.bin')))

def debug():
    shutil.copytree('/media/hankin/cp', '/media/test/')

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))