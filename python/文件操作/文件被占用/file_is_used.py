# -*- coding: utf-8 -*-
"""
文 件 名: file_is_used.py
文件描述: 文件或者文件夹被占用
作    者: HanKin
创建日期: 2023.02.22
修改日期：2023.02.22

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import re
import os
import win32file

def is_used(file_name):
    """
    """
    
    try:
        vHandle = win32file.CreateFile(file_name, win32file.GENERIC_READ, 0, None, win32file.OPEN_EXISTING, win32file.FILE_ATTRIBUTE_NORMAL, None)
        return int(vHandle) == win32file.INVALID_HANDLE_VALUE
    except:
        return True
    finally:
        try:
            win32file.CloseHandle(vHandle)
        except:
            pass
 

def main():
    """主函数
    """

    file_path = 'D:\\Users\\Administrator\\Desktop\\重在参与快乐加倍队'
    print(is_used(file_path))
    

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))