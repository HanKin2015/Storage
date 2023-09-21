# -*- coding: utf-8 -*-
"""
文 件 名: paramiko_timeout.py
文件描述: 使用paramiko库执行命令返回空字符串结果
作    者: HanKin
创建日期: 2023.09.20
修改日期：2023.09.20

Copyright (c) 2023 HanKin. All rights reserved.
"""

import paramiko
import time
import datetime

def paramiko_example1():
    """
    在连接之后，定期发送一些命令或请求以保持连接活动状态
    """
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect('172.22.65.15', username='root', password='1')

    for i in range(3):
        stdin, stdout, stderr = ssh.exec_command('pwd', timeout=100)
        timestamp = datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        print(timestamp, stdout.read())
        time.sleep(5)

def paramiko_example2():
    """
    在ssh.connect()方法中，timeout参数用于设置连接的超时时间。它指定了在尝试建立SSH连接时等待的最长时间。
    具体来说，timeout参数的作用如下：
    如果在指定的超时时间内无法建立SSH连接，将引发paramiko.ssh_exception.SSHException异常。
    如果连接成功建立，但在指定的超时时间内没有收到服务器的响应，将引发socket.timeout异常。
    通过设置适当的超时时间，可以控制连接建立的等待时间，以避免长时间等待而导致程序无响应或卡住。
    
    /usr/sbin/sshd -D是一个命令，用于启动SSH守护进程（SSH daemon）。SSH守护进程是一个在Linux系统上运行的后台进程，用于监听SSH连接请求并处理这些请求。当用户通过SSH连接到Linux系统时，SSH守护进程将负责验证用户身份、建立加密通道并启动一个新的Shell会话。
    
    使用ps aux | grep sshd可以查找到paramiko.SSHClient连接的进程，然后kill杀掉
    """
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect('172.22.65.15', username='root', password='1', timeout=20)
    
    for i in range(1000):
        timestamp = datetime.datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        try:
            stdin, stdout, stderr = ssh.exec_command('pwd', timeout=100)
        except paramiko.ssh_exception.SSHException:
            print(timestamp, 'paramiko.ssh_exception.SSHException')
            break

        print(timestamp, stdout.read())
        time.sleep(5)
    

def paramiko_example3():
    """
    定时检查连接进行重连
    """
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    while True:
        try:
            ssh.connect('172.22.65.15', username='root', password='1', timeout=20)
            break
        except paramiko.ssh_exception.SSHException:
            time.sleep(60)

def paramiko_example4():
    """
    我的问题是在使用ssh远程执行一句命令，但是给我返回了空字符串结果
    一开始我以为是ssh连接对象被断开了，但是目前测试好像不是
    还需要探索，可能是服务器删除了文件夹导致执行命令失败
    """
    pass

def main():
    """主函数
    """

    paramiko_example2()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    