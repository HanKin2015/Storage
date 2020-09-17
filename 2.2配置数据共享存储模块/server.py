# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:06:41 2020

@author: hj159
"""

# coding: utf-8

import socket
import time
import win32api, win32con 
import logging
import sys
import os

#当前进程pid
current_pid = os.getpid()
#当前进程监听的端口号
port = int(current_pid) + 5000

with open("./data/pids.run", "a") as f:
    f.write(str(port))
    f.write("\n")
with open("./data/pid.tmp", "w") as f:
    f.write(str(current_pid))
 
# 明确配置变量
ip_port = ('127.0.0.1',int(port))
back_log = 5
buffer_size = 1024
# 创建一个TCP套接字
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)   # 套接字类型AF_INET, socket.SOCK_STREAM   tcp协议，基于流式的协议
server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)  # 对socket的配置重用ip和端口号
# 绑定端口号
server.bind(ip_port)  #  写哪个ip就要运行在哪台机器上
# 设置半连接池
server.listen(back_log)  # 最多可以连接多少个客户端



logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='./log/server.log',
                    filemode='a')

def notify(pid, msg):
    msg = "进程{}对数据库有数据修改".format(pid)
    title = "数据更改通知机制{}".format(current_pid)
    win32api.MessageBox(0, msg, title, win32con.MB_OK)

def display_content(content):
    title = "通知"
    win32api.MessageBox(0, content, title, win32con.MB_OK)

def recv_msg():
    #消息编号
    index = 1    

    flag = False
    # 阻塞等待，创建连接
    print("开始监听('127.0.0.1',{})......".format(port))
    while True:
        con,address = server.accept()  # 在这个位置进行等待，监听端口号 
        while 1:
            try:
                # 接受套接字的大小，怎么发就怎么收
                msg = con.recv(buffer_size).decode('utf-8')
                if not msg:
                    continue
                tmp = msg.split(",")
                if len(tmp)!=2:
                    print("消息参数不对,msg={}".format(msg))
                    continue
                pid = tmp[0]
                msg = tmp[1]
                if msg=="close":
                    # 断开连接
                    con.close()
                    logging.info("断开连接")
                    print("断开连接")
                    flag = True
                    break
                logging.info("服务器收到消息{}: {}".format(index, msg))
                print("服务器收到消息{}: {}".format(index, msg))
                
                if msg=="notify":
                    notify(pid, msg)
                else:
                    display_content(msg)
                
            except Exception as e:
                logging.error("出现异常断开连接")
                con.close()
                break
            index+=1
            con.close()
        if flag:
            break

def close_server():    
    # 关闭服务器
    server.close()
    logging.info("服务端关闭成功")
    print("服务端关闭成功")