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
    """
    发送消息"close"关闭服务端程序
    """
    client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client.connect(('127.0.0.1',8383))

    if not msg:
        logging.error("输入了空的消息")
        client.close()
        logging.info("关闭连接成功")
    client.send(msg.encode('utf-8'))  # 收发消息一定要二进制，记得编码
    logging.info("发送消息 {} 成功".format(msg))
    
    client.close()
    logging.info("关闭连接成功")
    

    
    