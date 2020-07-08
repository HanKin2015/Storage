# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:26:35 2020

@author: hj159
"""

from socket import *
 
udp_ser = socket(AF_INET, SOCK_DGRAM)  # 数据报式的套接字
udp_ser.bind(('127.0.0.1', 8080))

import win32api, win32con
def Notify(msg):
	win32api.MessageBox(0, msg.decode(), "提醒", win32con.MB_OK)
 
while 1:
    data = udp_ser.recvfrom(1024)
    print(data)
    msg = data[0]
    if msg==b'close':
    	break
    Notify(msg)
    udp_ser.sendto('data'.encode('utf-8'),data[1])

udp_ser.close()
