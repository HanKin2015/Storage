# -*- coding: utf-8 -*-
"""
Created on Tue Aug 11 13:32:40 2020

@author: hankin

https://www.cnblogs.com/z3286586/p/11014468.html
"""

from ftplib import FTP
import os

def ftp_connect(host, username, password):
    """建立ftp连接

	Parameters
    ----------
    ftp : str
        ip地址
    username : str
        合法的sql语句
    password : 

    Returns
    -------
    bool
        成功返回True,失败False

	"""
    ftp = FTP()
    # ftp.set_debuglevel(2)
    ftp.connect(host, 21)
    ftp.login(username, password)
    return ftp

def download_file(ftp, remotepath, localpath):
    """从ftp下载文件

	Parameters
    ----------
    ftp : str
        创建的表的名称
    remotepath : str
        合法的sql语句
    localpath : 

    Returns
    -------
    bool
        成功返回True,失败False

	"""
    
    bufsize = 1024
    fp = open(localpath, 'wb')
    ftp.retrbinary('RETR ' + remotepath, fp.write, bufsize)
    ftp.set_debuglevel(0)
    fp.close()

def upload_file(ftp, remotepath, localpath):
    """从本地上传文件到ftp

	Parameters
    ----------
    ftp : str
        创建的表的名称
    remotepath : str
        合法的sql语句
    localpath : 

    Returns
    -------
    bool
        成功返回True,失败False

	"""
    bufsize = 1024
    fp = open(localpath, 'rb')
    ftp.storbinary('STOR ' + remotepath, fp, bufsize)
    ftp.set_debuglevel(0)
    fp.close()

if __name__ == "__main__":
    ftp = ftp_connect("199.200.5.88", "test", "test")
    download_file(ftp, "VDI/hj/1280x720_30fps_10s.mp4", "C:/Users/Administrator/Desktop/test.mp4")
    #调用本地播放器播放下载的视频
    os.system('start "C:\Program Files\Windows Media Player\wmplayer.exe" "C:/Users/Administrator/Desktop/test.mp4"')
    upload_file(ftp, "C:/Users/Administrator/Desktop/test.mp4", "test.mp4")

    ftp.quit()

    print("这是一个弹出提示框")
    #tkinter.messagebox.showinfo("提示","我是一个提示框")