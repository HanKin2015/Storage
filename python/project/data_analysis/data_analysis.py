# -*- coding: utf-8 -*-
"""
文 件 名: data_analysis.py
文件描述: 分析远程服务端数据
备    注: 
作    者: HanKin
创建日期: 2024.01.11
修改日期：2024.01.11

Copyright (c) 2024 HanKin. All rights reserved.
"""
import paramiko
import retrying
import traceback
import zipfile
import shutil
import os
import json
import tarfile

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

def debug():
    connect = ParamikoInterface("root", ip="12.12.15.15", password="1", port=22)
    stdout, stderr = connect.exec_command("uname -a")
    print("stdout:", stdout)
    print("stderr:", stderr)

def download_data(data_dir):
    # 建立连接
    connect = ParamikoInterface("root", ip="12.12.15.15", password="1", port=22)
    # 创建本地存储目录
    if not os.path.exists(data_dir):
        os.makedirs(data_dir)
    else:
        if os.path.isdir(data_dir):
            shutil.rmtree(data_dir, ignore_errors=True)
        os.makedirs(data_dir)
    # 压缩远程文件夹
    stdout, stderr = connect.exec_command("zip -r /root/device_data.zip /root/device_data")
    if stderr != "":
        print("zip diretory failed, {}".format(stderr))
        return False
    # 下载（本地需要写明压缩包文件名）
    if not connect.sftp_client:
        connect.get_sftp_client()
    data_path = os.path.join(data_dir, "device_data.zip")
    connect.sftp_client.get("/root/device_data.zip", data_path, callback=None)
    # 解压缩包
    zfile = zipfile.ZipFile(data_path)
    zfile.extractall(data_dir)
    zfile.close()
    # 删除临时压缩包
    connect.exec_command("rm -f /root/device_data.zip")
    os.remove(data_path)
    # 删除建立对象
    del connect
    return True

def download_data_by_tar(data_dir):
    # 建立连接
    connect = ParamikoInterface("root", ip="12.12.15.15", password="1", port=22)
    # 创建本地存储目录
    if not os.path.exists(data_dir):
        os.makedirs(data_dir)
    else:
        if os.path.isdir(data_dir):
            shutil.rmtree(data_dir, ignore_errors=True)
        os.makedirs(data_dir)
    # 压缩远程文件夹
    stdout, stderr = connect.exec_command("tar czf /root/device_data.tar /root/device_data")

    """这里必有警告信息
    在使用 tar 命令创建归档文件时，tar 默认会去除掉文件路径中的开头斜杠（/）。这样做的目的是为了安全，因为当你在解压归档文件时，去除开头的斜杠可以防止文件被解压到绝对路径，这可能会覆盖重要的系统文件。
    如果你想保留文件路径中的开头斜杠，可以使用 -P 或 --absolute-names 选项，这样 tar 就不会删除路径中的斜杠了。但请注意，这样做可能会带来安全风险，因为解压归档时会使用绝对路径。

    如果你不介意 tar 去除开头斜杠的行为，可以忽略这个警告。如果你的归档操作没有其他错误，那么归档文件应该已经成功创建。
    Removing leading `/' from member names
    """
    
    # 下载（本地需要写明压缩包文件名）
    if not connect.sftp_client:
        connect.get_sftp_client()
    data_path = os.path.join(data_dir, "device_data.tar")
    connect.sftp_client.get("/root/device_data.tar", data_path, callback=None)
    # 解压缩包
    with tarfile.open(data_path, 'r') as tar:
        tar.extractall(path=data_dir)
    # 删除临时压缩包
    connect.exec_command("rm -f /root/device_data.tar")
    os.remove(data_path)
    # 删除建立对象
    del connect

if __name__ == '__main__':
    data_dir = "./device_data"
    # 下载数据
    download_data(data_dir)
    # 提取数据
    for root, dirs, files in os.walk(data_dir):
        for file in files:
            # 处理文件
            if file.split(".")[-1] == "zip":
                file_path = os.path.join(root, file)
                print(file_path)
                # 解压缩包
                zfile = zipfile.ZipFile(file_path)
                zfile.extractall(data_dir)
                for file_name in os.listdir(data_dir):
                    full_path = os.path.join(data_dir, file_name)
                    if os.path.isfile(full_path):
                        # 处理文件
                        print(full_path)
                        with open(full_path) as f:
                            device_info = json.load(f)
                        print(device_info)
                        
                        os.remove(full_path)
                    else:
                        pass  # 递归处理子文件夹
                    
                
    