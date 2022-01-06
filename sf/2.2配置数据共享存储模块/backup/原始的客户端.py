# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:11:29 2020

@author: hj159
"""

import socket
import os
 
p = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
p.connect(('127.0.0.1',8383))
while 1:
    msg = input("输入发送的消息(close断开连接): ")
    # 防止输入空消息
    if not msg:
        continue
    p.send(msg.encode('utf-8'))  # 收发消息一定要二进制，记得编码
    print("发送成功")
    if msg == "close":
        print("断开连接")
        break

p.close()
print("关闭连接成功")