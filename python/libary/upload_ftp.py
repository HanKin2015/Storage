# -*- coding: utf-8 -*-
"""
Created on Thu Aug 13 09:43:47 2020

@author: Administrator
"""

import win32api,win32con
from ftplib import FTP

def ftpconnect(host, username, password):
    """
    
    """
    ftp = FTP()
    # ftp.set_debuglevel(2)
    ftp.connect(host, 21)
    ftp.login(username, password)
    return ftp

# 从ftp下载文件
def downloadfile(ftp, remotepath, localpath):
    bufsize = 1024
    fp = open(localpath, 'wb')
    ftp.retrbinary('RETR ' + remotepath, fp.write, bufsize)
    ftp.set_debuglevel(0)
    fp.close()

# 从本地上传文件到ftp
def uploadfile(ftp, remotepath, localpath):
    bufsize = 1024
    fp = open(localpath, 'rb')
    ftp.storbinary('STOR ' + remotepath, fp, bufsize)
    ftp.set_debuglevel(0)
    fp.close()
    
if __name__ == "__main__":
    ftp = ftpconnect("199.200.5.88", "test", "test")
    uploadfile(ftp, "VDI/hj/msg_between_extranet_and_intranet.txt", "D:/Github/Storage/python/msg_between_extranet_and_intranet.txt")
    # 提醒OK消息框
    win32api.MessageBox(0, "上传成功", "提醒", win32con.MB_OK)
    ftp.quit()


  

