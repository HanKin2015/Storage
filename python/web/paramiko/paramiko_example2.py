# -*- coding: utf-8 -*-
"""
文 件 名: paramiko_example2.py
文件描述: TypeError: '<' not supported between instances of 'int' and 'str'
作    者: HanKin
创建日期: 2023.09.18
修改日期：2023.09.18

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
import paramiko
import time
import logging
import sys
import retrying
import traceback
import base64
import re

class ConnectHost:

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
            print(traceback.format_exc())

    def put_file_to_remote(self, local_path, remote_path):
        try:
            if not self.sftp_client:
                self.get_sftp_client()
            self.sftp_client.put(local_path, remote_path)
        except:
            print("put file {0} to {1}:{2}{3}  failed.".format(local_path, self.ip, self.port, remote_path))
            print(traceback.format_exc())

    def get_file_from_remote(self, remote_path, local_path, callback=None):
        try:
            if not self.sftp_client:
                self.get_sftp_client()
            self.sftp_client.get(remote_path, local_path, callback=callback)
        except:
            print("get file {0} from {1}:{2}{3} failed.".format(local_path, self.ip, self.port, remote_path))
            print(traceback.format_exc())

    # ssh client
    def get_ssh_client(self):
        try:
            # 创建ssh对象
            ssh_client = paramiko.SSHClient()
            ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            ssh_client.connect(self.ip, self.port, self.user, self.password, timeout=5)
            self.ssh_client = ssh_client
            return ""
        except Exception as e:
            print("ssh connect to {0}:{1} failed.".format(self.ip, self.port))
            print(str(e))
            if isinstance(e, paramiko.ssh_exception.AuthenticationException):
                return "authentication failed"
            elif "timed out" in str(e):
                return "ssh connection timed out"
            elif "SSH protocol banner" in str(e):
                return "port error"
            else:
                return "unknown exception"

    # 最大重试次数为5次，重试时间间隔为3秒
    @retrying.retry(stop_max_attempt_number=5, wait_fixed=3000)
    def exec_command(self, cmd, time=10000, **kwargs):
        try:
            if not self.ssh_client:
                self.get_ssh_client()
            if self.ssh_client == None:
                print("self.ssh_client is None")
                return None
            stdin, stdout, stderr = self.ssh_client.exec_command(cmd, timeout=time)
            need_stderr = kwargs.get("stderr", "")
            need_encoding = kwargs.get("encoding", "")
            need_rawdata = kwargs.get("rawdata", "")
            if need_encoding and need_stderr:
                retout = stdout.read().decode("GBK")
                reterr = stderr.read().decode()
                return retout, reterr
            elif need_stderr:
                retout = stdout.read().decode()
                reterr = stderr.read().decode()
                return retout, reterr
            elif need_encoding:
                retout = stdout.read().decode("GBK")
                return retout
            elif need_rawdata:
                return stdout,stderr
            else:
                retout = stdout.read().decode()
                return retout
        except:
            print("exe [ {0} ] at {1}:{2} failed.".format(cmd, self.ip, self.port))
            print(traceback.format_exc())
            return None

    def __del__(self):
        if self.ssh_client:
            self.ssh_client.close()
        elif self.sftp_client:
            self.sftp_client.close()
        else:
            pass

def main():
    """主函数
    """

    connect_host = ConnectHost("root", ip="172.22.65.15", password="1", port="22")
    try:
        uname = connect_host.exec_command("uname -a")
        connect_host.put_file_to_remote("patrol.log", "/media/hejian.log")
    except:
        print(traceback.format_exc())
    print("uname: {}".format(uname))

if __name__ == '__main__':
    """程序入口
    """

    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    