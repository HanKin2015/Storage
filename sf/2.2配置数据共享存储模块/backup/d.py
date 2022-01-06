# -*- coding: utf-8 -*-
"""
Created on Wed Jul  8 02:26:18 2020

@author: hj159
"""

from socket import *
 
s = socket(AF_INET, SOCK_DGRAM)
while 1:
    msg = input('input-1')
    s.sendto(msg.encode('utf-8'), ('127.0.0.1', 8080))
    if msg=='close':
    	break
    data,addr = s.recvfrom(1024)
    print(data.decode('utf-8'))
s.close()
