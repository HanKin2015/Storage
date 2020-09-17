# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 13:35:12 2020

@author: hejian29996
@description:
    客户端使用的socket通信模块，负责收发消息
"""

import os
import socket
import logging
import sys
import threading

# 日志文件夹路径
log_path = './log'
log_name = '/client_socket_service.log'

# 当前进程pid
current_pid = os.getpid()

# 服务监听配置
ip = '127.0.0.1'
port = current_pid + 5000

# 建立必要的文件夹
if not os.path.exists(log_path):
    os.makedirs(log_path)

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename=log_path+log_name,
                    filemode='a')


def start_server_thread():
    global g_server_thread
    g_server_thread = threading.Thread(target=server.recv_msg)
    g_server_thread.setDaemon(True)
    g_server_thread.start()
    return True

def init():
    global g_self_server_pid, g_server_thread
    #os.popen(".\\dist\\server\\server.exe")
    start_server_thread()

    time.sleep(0.5)
    with open("./data/pid.tmp", "r") as f:
        g_self_server_pid = f.read()
        #print(g_self_server_pid)

    ret = send_message("{},connect".format(g_self_server_pid))

    with open("./pid.txt", "a") as f:
        f.write(str(os.getpid()))
        f.write("\n")

    return ret

def main():

if __name__=='__main__':
    # 初始化：拉起自身的server
    ret = init()
    if not ret:
        print("程序无法启动.")
        sys.exit()
    parse_argument()
    #main()
    #os.popen('taskkill.exe /f /pid:'+str(g_self_server_pid))  

    
    
    
    
    