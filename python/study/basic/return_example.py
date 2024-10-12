# -*- coding: utf-8 -*-
"""
文 件 名: return_example.py
文件描述: 在 Python 中，return 语句只能在函数内部使用，而不能在全局作用域中使用
作    者: HanKin
创建日期: 2024.10.12
修改日期：2024.10.12

Copyright (c) 2024 HanKin. All rights reserved.
"""
import sys

def download_files():
    # 下载文件的逻辑
    print("Downloading files...")

def upload_files():
    # 上传文件的逻辑
    print("Uploading files...")
    print(x)

if __name__ == '__main__':
    argv_cnt = len(sys.argv)
    if argv_cnt == 2:
        print('download files')
        download_files()
        #return     # SyntaxError: 'return' outside function
        sys.exit()  # 使用 sys.exit() 退出程序
    # __main__函数是全局作用域
    x = 3158
    print('upload files')
    upload_files()

'''
(base) D:\Github\Storage\python\study\basic>python return_example.py
upload files
Uploading files...
3158
'''