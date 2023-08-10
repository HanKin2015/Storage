# -*- coding: utf-8 -*-
"""
文 件 名: judge_file_or_directory.py
文件描述: ftp服务器中判断是文件还是文件夹
参    考: https://stackoverflow.com/questions/1088336/ftplib-checking-if-a-file-is-a-folder
作    者: HanKin
创建日期: 2023.08.10
修改日期：2023.08.10

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
from ftplib import FTP
import time

def use_ftputil():
    """pip install ftputil可行
    """
    
    import ftputil
    # 使用了getwelcome()方法来获取FTP服务器的欢迎信息。如果FTP服务器支持匿名登录，那么您应该能够成功连接并列出FTP服务器上的文件。如果FTP服务器不支持匿名登录，那么您需要联系FTP服务器管理员以获取正确的账号和密码。
    with ftputil.FTPHost('172.22.64.246', 'anonymous', '') as ftp_host:
        ftp_host.chdir('/')   
        list = ftp_host.listdir(ftp_host.curdir)
        for fname in list:
            if ftp_host.path.isdir(fname):
                print(fname.encode('latin-1').decode('gbk') + " is a directory")
            else:
                print(fname.encode('latin-1').decode('gbk') + " is not a directory")
            
def is_file(filename):
    """ftplib.error_perm: 550-Access is denied.使用管理员运行结果还是一样，不可取
    """
    
    return ftp.size(filename) is not None

def use_sendcmd(ftp):
    """ftplib.error_perm: 500 Command not understood.
    """
    
    return ftp.sendcmd('MLST /')

def use_cwd(ftp, path):
    """TypeError: argument of type 'error_perm' is not iterable
    """
    
    try:
        ftp.cwd(path)
    except Exception as e:
        if "550" in e:
            return True
    return False

def judge_file_or_directory(ftp, path):
    """估计是中文乱码不可行
    """
    
    print(ftp.nlst(path), path)
    if ftp.nlst(path) == [path]:
        return True
    else:
        return False

def main():
    """主函数
    """
    
    # 连接 FTP 服务器
    ftp = FTP('172.22.64.246')
    ftp.login(user='', passwd='')
    
    # 打印FTP服务器欢迎信息
    print('111', ftp.getwelcome())
    
    # 获取目录列表
    directory = ftp.nlst('/')
    for elem in directory:
        print(elem.encode('latin-1').decode('gbk'))
    # 直接打印会有中文乱码问题，另外一种方法是修改开源库https://blog.csdn.net/wenzhp1975/article/details/104896404
    #print(directory)

    # 路径是中文时https://www.fengnayun.com/news/content/137570.html
    file_path = u'/捕获.PNG'
    print(judge_file_or_directory(ftp, file_path.encode(encoding='gbk').decode(encoding='latin-1')))
    dir_path = u'/神思相关软件'
    print(judge_file_or_directory(ftp, dir_path.encode(encoding='gbk').decode(encoding='latin-1')))

    # 关闭 FTP 连接
    ftp.quit()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    use_ftputil()
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
