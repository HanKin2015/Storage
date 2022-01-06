# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 18:47:28 2020

@author: Administrator
"""

__author__ = 'hejian29996'
 
import os, socket, threading, socketserver

SERVER_HOST='localhost'
SERVER_PORT=0
BUF_SIZE=1024
ECHO_MSG='HELLO'
 
class ForkedClient():
    def __init__(self,ip,port):
        #建立sock
        self.sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        #连接server
        self.sock.connect((ip,port))
 
    def run(self):
        #获取当前的进程号
        current_process_id=os.getpid()
        print('PID %s ：" "%s"'%(current_process_id,ECHO_MSG))
        sent_data_length = self.sock.send(ECHO_MSG.encode())
        print('发送:%d 长数据' % sent_data_length)
        #sever response
        response=self.sock.recv(BUF_SIZE)
        print("PID %s received: %s" % (current_process_id,response))
 
    def shutdown(self):
        '''
        清理sock的资源
        :return:
        '''
        self.sock.close()
         
class ForkingServerRequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        #接受客户端的数据
        data=self.request.recv(BUF_SIZE)
        #当前的进程号码
        current_process_id=os.getpid()
        #返回的数据包
        response='%s: %s' % (current_process_id, data)
        print("服务器返回 [current_process_id: data] =[%s]" %response)
        #发送返回数据
        self.request.send(response.encode())
        return
 
class ForkingServer(socketserver.ThreadingMixIn,socketserver.TCPServer):
    pass
 
def main():
    #建立server
    server=ForkingServer((SERVER_HOST,SERVER_PORT),ForkingServerRequestHandler)
    #获取IP 和 端口
    ip, port = server.server_address # Retrieve the port number
    #服务进程
    server_thread = threading.Thread(target=server.serve_forever)
    #是否放入后台
    server_thread.setDaemon(True) # don't hang on exit
    #启动
    server_thread.start()
    print('Server loop running PID: %s' %os.getpid())
    # Launch the client(s)
    client1 =  ForkedClient(ip, port)
    client1.run()
    client2 =  ForkedClient(ip, port)
    client2.run()
    # Clean them up
    server.shutdown()
    client1.shutdown()
    client2.shutdown()
    server.socket.close()
if __name__ == '__main__':
    main()