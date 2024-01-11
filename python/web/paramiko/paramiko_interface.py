# -*- coding: utf-8 -*-
"""
文 件 名: paramiko_interface.py
文件描述: paramiko库封装的类接口
备    注: 
作    者: HanKin
创建日期: 2024.01.08
修改日期：2024.01.08

Copyright (c) 2024 HanKin. All rights reserved.
"""
import paramiko
import retrying
import traceback

class ParamikoInterface:
    def __init__(self, user, ip, password, port):
        self.ip = ip
        self.user = user
        self.password = password
        self.port = port
        self.ssh_client = None
        self.sftp_client = None

    def get_sftp_client(self):
        try:
            # 建立一个加密的管道
            transport = paramiko.Transport(self.ip, self.port)
            # 建立连接
            transport.connect(username=self.user, password=self.password)
            # 建立一个sftp客户端对象，通过ssh transport操作远程文件
            self.sftp_client = paramiko.SFTPClient.from_transport(transport)
        except:
            print("sftp connect to {0}:{1} {2} failed.".format(self.ip, self.port, self.user))

    def get_ssh_client(self):
        try:
            # 创建ssh对象
            ssh_client = paramiko.SSHClient()
            ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            ssh_client.connect(self.ip, self.port, self.user, self.password, timeout=5)
            self.ssh_client = ssh_client
            return ""
        except Exception as err:
            print("ssh connect to {0}:{1} failed. {}".format(self.ip, self.port, str(err)))
            if isinstance(err, paramiko.ssh_exception.AuthenticationException):
                return "authentication failed"
            elif "timed out" in str(err):
                return "ssh connection timed out"
            elif "SSH protocol banner" in str(err):
                return "port error"
            else:
                return "unknown exception"

    # 最大重试次数为5次，重试时间间隔为3秒
    @retrying.retry(stop_max_attempt_number=5, wait_fixed=3000)
    def exec_command(self, cmd, timeout=50000):
        try:
            if not self.ssh_client:
                self.get_ssh_client()
            if self.ssh_client == None:
                printf("self.ssh_client is None")
                return None, None
            stdin, stdout, stderr = self.ssh_client.exec_command(cmd, timeout=timeout)
            retout = stdout.read().decode("GBK")
            reterr = stderr.read().decode()
            return retout, reterr

        except:
            print("exec command [ {0} ] at {1}:{2} failed.".format(cmd, self.ip, self.port))
            print(traceback.format_exc())
            return None, None

    def __del__(self):
        if self.ssh_client:
            self.ssh_client.close()
        elif self.sftp_client:
            self.sftp_client.close()
        else:
            pass

if __name__ == '__main__':
    connect = ParamikoInterface("root", ip="172.22.65.15", password="1", port=22)
    stdout, stderr = connect.exec_command("ls")
    print("stdout:", stdout)
    print("stderr:", stderr)
    
    
    