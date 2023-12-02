# -*- coding: utf-8 -*-
"""
文 件 名: socket_server_example.py
文件描述: 网络编程
作    者: HanKin
创建日期: 2023.12.02
修改日期：2023.12.02

Copyright (c) 2023 HanKin. All rights reserved.
"""

# Socket编程
import socket

# 创建套接字
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 绑定地址和端口
server_socket.bind(('127.0.0.1', 12345))

# 监听连接
server_socket.listen(1)

# 接受连接
conn, addr = server_socket.accept()

# 接收数据
data = conn.recv(1024)
print('Received:', data.decode())

# 发送数据
conn.sendall(b'Hello, client!')

# 关闭连接
conn.close()

