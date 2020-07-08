# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:06:41 2020

@author: hj159
"""

# coding: utf-8

import socket
import time
import win32api, win32con 
 
# 明确配置变量
ip_port = ('127.0.0.1',8383)
back_log = 5
buffer_size = 1024
# 创建一个TCP套接字
ser = socket.socket(socket.AF_INET,socket.SOCK_STREAM)   # 套接字类型AF_INET, socket.SOCK_STREAM   tcp协议，基于流式的协议
ser.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)  # 对socket的配置重用ip和端口号
# 绑定端口号
ser.bind(ip_port)  #  写哪个ip就要运行在哪台机器上
# 设置半连接池
ser.listen(back_log)  # 最多可以连接多少个客户端


def Notify(msg):
	win32api.MessageBox(0, msg, "提醒", win32con.MB_OK)

#消息编号
index = 1    

# 阻塞等待，创建连接
print("开始监听('127.0.0.1',8383)......")
con,address = ser.accept()  # 在这个位置进行等待，监听端口号 
while 1:
    try:
        # 接受套接字的大小，怎么发就怎么收
        time.sleep(2)
        msg = con.recv(buffer_size).decode('utf-8')
        if msg=="close":
            # 断开连接
            con.close()
            print("断开连接")
            break
        print("服务器收到消息{}: ".format(index), msg)
        
        if msg=="notify":
            Notify(msg)
        
    except Exception as e:
        print("出现异常断开连接")
        con.close()
        break
    index+=1
    
# 关闭服务器
ser.close()
print("服务端关闭成功")
