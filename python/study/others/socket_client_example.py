# -*- coding: utf-8 -*-
"""
文 件 名: socket_client_example.py
文件描述: socket编程之客户端
作    者: HanKin
创建日期: 2023.12.02
修改日期：2023.12.02

Copyright (c) 2023 HanKin. All rights reserved.
"""
import socket

# 创建套接字
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 连接服务器
client_socket.connect(('127.0.0.1', 12345))

# 发送数据
client_socket.sendall(b'Hello, server!')

# 接收数据
data = client_socket.recv(1024)
print('Received:', data.decode())

# 关闭连接
client_socket.close()
