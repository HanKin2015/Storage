# -*- coding: utf-8 -*-
"""
Created on Tue Sep  1 19:36:49 2020

@author: hankin
@description:
    copy tool for ftp
"""

import tkinter as tk
import tkinter.font as tf
import win32api,win32con
from ftplib import FTP

ip = "199.200.5.88"
user = "test"
password = "test"
remote_file_path = "VDI/hj/msg_between_extranet_and_intranet.txt"
local_file_path = "D:/msg_between_extranet_and_intranet.txt"

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

def set_win_center(root, cur_width='', cur_height=''):
    '''
    设置窗口大小，并居中显示
    :param root:主窗体实例
    :param cur_width:窗口宽度，非必填，默认200
    :param cur_height:窗口高度，非必填，默认200
    :return:无
    '''
    if not cur_width:
        '''获取窗口宽度，默认200'''
        cur_width = root.winfo_width()
    if not cur_height:
        '''获取窗口高度，默认200'''
        cur_height = root.winfo_height()
    # print(cur_width, cur_height)

    # 获取屏幕宽度和高度
    scn_w, scn_h = root.maxsize()
    # print(scn_w, scn_h)

    # 计算中心坐标
    cen_x = (scn_w - cur_width) / 2
    cen_y = (scn_h - cur_height) / 2
    # print(cen_x, cen_y)

    # 设置窗口初始大小和位置
    size_xy = '%dx%d+%d+%d' % (cur_width, cur_height, cen_x, cen_y)
    root.geometry(size_xy)

def upload_btn_cliecked(display_content):
    '''
    发送按钮点击事件
    '''
    content = display_content.get('0.0', 'end').strip()
    print('正在写入', local_file_path)
    try:
        with open(local_file_path, 'w', encoding='utf-8') as f:
            f.write(content)
    except Exception as ex:
        print('打开文件失败, error=', ex)
        
    ftp = ftp_connect(ip, user, password)
    upload_file(ftp, remote_file_path, local_file_path)
    # 提醒OK消息框
    win32api.MessageBox(0, "上传成功", "提醒", win32con.MB_OK)
    ftp.quit()
    
def download_btn_cliecked(display_content):
    '''
    接收消息按钮点击事件
    
    :param display_content:Text组件
    '''
    ftp = ftp_connect(ip, user, password)
    download_file(ftp, remote_file_path, local_file_path)
    
    print('正在读取', local_file_path)
    content_list = []
    
    try:
        with open(local_file_path, 'r', encoding='utf-8') as f:
            content_list = f.readlines() 
    except Exception as ex:
        print('打开文件失败, error=', ex)
    
    content = ''
    for elem in content_list:
        content = content + elem
    
    display_content.delete('0.0', 'end')
    display_content.insert('insert', content)
    
def copy_btn_cliecked(display_content):
    '''
    复制内容按钮点击事件
    '''
    # 打印显示内容
    content = display_content.get('0.0', 'end').strip()
    print(content)
    
    # 将内容弄到剪切板
    display_content.event_generate("<<SelectAll>>")
    display_content.event_generate("<<Copy>>")

def send_recv_msg():
    '''
    send and recive message, intranet extranet
    ui界面设计
    '''
    root = tk.Tk()
    root.title('copy tool')
    root.resizable(False, False)
    root.update()
    set_win_center(root, 600, 600)
    
    # 设置字体slant=tf.ITALIC,underline=1,overstrike=1
    ft = tf.Font(family='consolas', weight=tf.BOLD, size=12)  
    
    # 上面部分
    fm_up = tk.Frame()
    input_content = tk.Entry(fm_up, width=30, font=ft)
    input_content.pack(side=tk.LEFT, expand=True, fill=tk.X, padx=5, pady=5)
    upload_btn = tk.Button(fm_up,text='send', width=10, height=1,\
                           command=lambda:upload_btn_cliecked(display_content), font=ft, compound='center') 
    upload_btn.pack(side=tk.LEFT, pady=5)     
    download_btn = tk.Button(fm_up,text='recive', width=10, height=1,\
                             command=lambda:download_btn_cliecked(display_content), font=ft, compound='center') 
    download_btn.pack(side=tk.LEFT, padx=5) 
    
    fm_up.pack(fill=tk.X)
    
    # 下面部分：显示内容和拷贝按钮
    fm_down = tk.Frame()
    display_content = tk.Text(fm_down, font=ft)
    display_content.pack(side=tk.TOP, fill=tk.Y, expand=True, padx=5)
    
    copy_btn = tk.Button(fm_down,text='copy', command=lambda:copy_btn_cliecked(display_content), font=ft, compound='center') 
    copy_btn.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
    fm_down.pack(fill=tk.BOTH, expand=True)
    
    root.mainloop()

    
if __name__ == "__main__":
    send_recv_msg()
    
    
    
    
    
    