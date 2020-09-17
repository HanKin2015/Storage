# -*- coding: utf-8 -*-
"""
Created on Sat Jul  4 16:30:36 2020

@author: hejian29996
@description: 
    服务端开启接收消息服务程序
"""

import configure_data_share_storage_service		# 配置数据共享存储服务库
import os, time

ip = '127.0.0.1'
server_port = 8384
print('当前进程:{}'.format(os.getpid()))

if __name__ == '__main__':
	server = configure_data_share_storage_service.server_socket_library()
	# 开启服务端socket守护线程
	configure_data_share_storage_service.start_socket_thread(server, ip, server_port)

	time.sleep(180)