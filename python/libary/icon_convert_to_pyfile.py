# -*- coding: utf-8 -*-
"""
文 件 名: icon_convert_to_pyfile.py
文件描述: 把图片文件转换成py文件保存
备    注: 图片使用时需要base64.b64decode(udev_detect_ico)转换
作    者: HanKin
创建日期: 2023.02.27
修改日期：2023.03.11

Copyright (c) 2023 HanKin. All rights reserved.
"""


import base64
import time
import os

PY_FILE_PATH = './ico.py'

def ico2py(ico_file_name):
    """
    """
    
    ico_file_path = '../img/{}.ico'.format(ico_file_name)

    ico = open(ico_file_path, 'rb')
    ico_str = base64.b64encode(ico.read())
    ico_content = '{}_ico = {}'.format(ico_file_name, str(ico_str))

    fp = open(PY_FILE_PATH, 'a+')
    fp.write(ico_content)
    fp.write('\n')
    ico.close()
    fp.close()

def main():
    """主函数
    """
    
    if os.path.exists(PY_FILE_PATH):
        os.remove(PY_FILE_PATH)
    ico2py('udev_detect')
    ico2py('msg')

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))