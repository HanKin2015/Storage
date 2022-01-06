# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:11:29 2020

@author: hj159
"""

import socket
import os
import logging

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='./log/client.log',
                    filemode='a')

def Send(msg):
client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client.connect(('127.0.0.1',8383))
while 1:
    msg = input("输入发送的消息(close断开连接): ")
    # 防止输入空消息
    if not msg:
        continue
    client.send(msg.encode('utf-8'))  # 收发消息一定要二进制，记得编码
    logging.info("发送消息 {} 成功".format(msg))
    if msg=="close":
        logging.info("断开连接")
        break

client.close()
logging.info("关闭连接成功")