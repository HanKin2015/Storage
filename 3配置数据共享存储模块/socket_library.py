# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 13:35:12 2020

@author: hejian29996
@description:
    客户端使用的socket通信模块，负责收发消息
"""

import socket
import os
import logging

# 收到消息的大小
buffer_size = 1024
# 客户端最多连接数量
listen_client_maxcnt = 5

# 日志文件夹路径
log_path = './log'
log_name = '/socket_library.log'

# 建立必要的文件夹
if not os.path.exists(log_path):
    os.makedirs(log_path)

# 配置日志
logger = logging.getLogger(__name__)
logger.setLevel(level = logging.INFO)
fh = logging.FileHandler(log_path+log_name, mode='a')
fh.setLevel(logging.INFO)  
formatter = logging.Formatter('%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s')
fh.setFormatter(formatter)
logger.addHandler(fh)

class socket_library:
    def send_message(self, ip, port, msg, pid=2020):
        """发送消息.

        主要负责数据库更改通知，向客户端发送更改通知消息

        Parameters
        ----------
        ip : str
            向哪个地址发送消息
        port : int
            向哪个端口发送消息
        msg : str
            消息内容
        pid : int
            那个进程对数据库进行了更改
            
        Returns
        -------
        bool
            发送成功返回True，失败False
        """
        
        try:
            client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
            client.connect((ip, port))
            logger.info("连接端口{}成功".format(port))
        except:
            logger.error("连接失败,端口{}可能未开启".format(port))
            return False

        send_msg = "{},{}".format(pid, msg)
        client.send(send_msg.encode('utf-8'))  # 收发消息一定要二进制，记得编码
        logger.info("进程{}向{}端口发送消息:{}".format(pid, port, send_msg))
        client.close()
        return True

    def parse_data(self, data):
        """解析数据.

        主要对接收的消息解析，消息结构为pid,content.

        Parameters
        ----------
        data : data
            解析的数据

        Returns
        -------
        pid : int
            数据来源的进程id
        content : str
            消息内容
        """

        idx = data.strip().find(',')
        if idx == -1:
            logger.error("数据格式错误，当前数据为:{}".format(data))
            return None
        pid = data.strip()[:idx]
        content = data.strip()[idx+1:]

        logger.info("解析完成后:pid = [{}], msg = [{}]".format(pid, content))
        return pid, content

    def recv_message(self, ip, port):
        """接收消息.

        主要负责接收客户端建立连接消息.
        
        Parameters
        ----------
        ip : str
            向哪个地址发送消息
        port : int
            向哪个端口发送消息
        """

        # 创建一个TCP套接字
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   # 套接字类型AF_INET, socket.SOCK_STREAM   tcp协议，基于流式的协议
        server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR, 1)  # 对socket的配置重用ip和端口号
        # 绑定端口号
        server.bind((ip, port))  # 写哪个ip就要运行在哪台机器上
        # 设置半连接池
        server.listen(listen_client_maxcnt)  # 最多可以连接多少个客户端

        while True:
            try:
                logger.info("开始监听{}......".format((ip, port)))
                # 阻塞等待，创建连接
                con, address = server.accept()  # 在这个位置进行等待，监听端口号 
            except Exception as e:
                logger.error("创建连接失败，请检查端口是否已经被占用。")
                break
            
            # 接受套接字的大小，怎么发就怎么收
            recv_msg = con.recv(buffer_size).decode('utf-8')
            logger.info("收到消息:{}".format(recv_msg))
            con.close()

            pid, msg = self.parse_data(recv_msg)
            
            # 返回结果给主进程，主进程重写
            self.parse_msg(pid, msg)

    def parse_msg(pid, msg):
        pass
    
    
    
    