# -*- coding: utf-8 -*-
"""
文 件 名: file_attribute.py
文件描述: 文件属性获取
作    者: HanKin
创建日期: 2022.06.09
修改日期：2022.06.09

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import stat
import time

FILE_PATH = 'D:\Github\Storage\c++\lzo\install_lzo.sh'
path = FILE_PATH

def test_os_path():
    print(os.path.getsize(FILE_PATH))
    print(os.path.abspath(FILE_PATH))
    print(os.path.exists(FILE_PATH))
    print(os.path.getatime(path))	#返回最近访问时间（浮点型秒数）
    print(os.path.getmtime(path))	#返回最近文件修改时间
    print(os.path.getctime(path))   #返回文件 path 创建时间
    print(os.path.getsize(path))	#返回文件大小，如果文件不存在就返回错误
    print(os.path.isabs(path))	    #判断是否为绝对路径
    print(os.path.isfile(path))	    #判断路径是否为文件
    print(os.path.isdir(path))	    #判断路径是否为目录
    print(os.path.islink(path))	    #判断路径是否为链接
    print(os.path.ismount(path))    #判断路径是否为挂载点

def test_os_stat():
    fd = os.stat(FILE_PATH)
    
    print(fd)
    print(fd.st_mode, fd.st_ino, fd.st_dev, fd.st_nlink)
    print(fd.st_atime, fd.st_mtime, fd.st_ctime)
    print(time.strftime("%Y-%m-%d %X", time.localtime(fd.st_ctime)))
    print(time.strftime("%Y-%m-%d %X", time.localtime(1454623587)))
    
    # os.stat是将文件的相关属性读出来，然后用stat模块来处理
    mode = fd.st_mode
    if stat.S_ISDIR(mode):
        print('is directory.')
    elif stat.S_ISREG(mode):
        print('is reg.')
    else:
        print('')
    
    IsRead    = bool(stat.S_IREAD & mode)
    IsWrite   = bool(stat.S_IWRITE & mode)
    IsExecute = bool(stat.S_IEXEC & mode)
    print(IsExecute, IsRead, IsWrite)
    # 想了解更多：https://blog.csdn.net/qdPython/article/details/118522329
        
if __name__ == '__main__':
    test_os_path()
    print('\n', '-'*150, '\n')
    test_os_stat()