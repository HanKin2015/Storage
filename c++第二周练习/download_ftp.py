# -*- coding: utf-8 -*-
"""
Created on Thu Aug 13 09:40:53 2020

@author: Administrator
"""

import tkinter as tk
from ftplib import FTP

def ftpconnect(host, username, password):
    """
    
    """
    ftp = FTP()
    # ftp.set_debuglevel(2)
    ftp.connect(host, 21)
    ftp.login(username, password)
    return ftp

#从ftp下载文件
def downloadfile(ftp, remotepath, localpath):
    bufsize = 1024
    fp = open(localpath, 'wb')
    ftp.retrbinary('RETR ' + remotepath, fp.write, bufsize)
    ftp.set_debuglevel(0)
    fp.close()

#从本地上传文件到ftp
def uploadfile(ftp, remotepath, localpath):
    bufsize = 1024
    fp = open(localpath, 'rb')
    ftp.storbinary('STOR ' + remotepath, fp, bufsize)
    ftp.set_debuglevel(0)
    fp.close()



def display_content(content):
    """
    """
    root = tk.Tk()
    root.title('外网内容')
     
    text = tk.Text(root, width=120, height=30)
    text.pack()
 
    # 设置 tag
    text.tag_config("tag_1", backgroun="yellow", foreground="red")

     
    # "insert" 索引表示插入光标当前的位置
    text.insert("insert", content)
    text.insert("end", "\n\nby hj", "tag_1")
    tk.Button(root,text='copy').pack(fill=tk.X)
    
    def enterTag(event):
        print('Enter event')
    #text.tag_bind('a','<Enter>',enterTag)
    #text.insert(2.0,'Enter event\n','a')
     
    root.mainloop()
    
if __name__ == "__main__":
    ftp = ftpconnect("199.200.5.88", "test", "test")
    downloadfile(ftp, "VDI/hj/msg_between_extranet_and_intranet.txt", "D:/Users/User/Desktop/msg_between_extranet_and_intranet.txt")
    
    
    file_path = "D:/Users/User/Desktop/msg_between_extranet_and_intranet.txt"
    print('正在读取', file_path)
    content_list = []
    
    try:
        with open(file_path, 'r', encoding='gbk') as f:
            content_list = f.readlines() 
    except Exception as ex:
        print('打开文件失败, error=', ex)
    
    print(type(content_list))
    
    content = ''
    for elem in content_list:
        content = content + elem
    display_content(content)
    
    
    
    