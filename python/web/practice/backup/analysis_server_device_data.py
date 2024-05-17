# -*- coding: utf-8 -*-
"""
文 件 名: analysis_server_device_data.py
文件描述: 将服务端的zip文件下载到本地进行分析
备    注: 
作    者: HanKin
创建日期: 2024.01.05
修改日期：2024.04.03

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

def download_data(data_dir):
    # 建立连接
    connect = ParamikoInterface("root", ip="xx.xx.xx.xx", password="xxxxx", port=22)
    # 创建本地存储目录
    if not os.path.exists(data_dir):
        print("makedirs {}".format(data_dir))
        os.makedirs(data_dir)
    else:
        if os.path.isdir(data_dir):
            print("rmtree {}".format(data_dir))
            shutil.rmtree(data_dir, ignore_errors=False)
        print("makedirs {}".format(data_dir))
        os.makedirs(data_dir)
    # 压缩远程文件夹
    stdout, stderr = connect.exec_command("tar czf /usr/local/adesk/device_data.tar /usr/local/adesk/device_data")
    # 下载（本地需要写明压缩包文件名）
    if not connect.sftp_client:
        connect.get_sftp_client()
    data_path = os.path.join(data_dir, "device_data.tar")
    connect.sftp_client.get("/usr/local/adesk/device_data.tar", data_path, callback=None)
    # 解压缩包
    with tarfile.open(data_path, 'r') as tar:
        tar.extractall(path=data_dir)
    # 删除临时压缩包
    connect.exec_command("rm -f /usr/local/adesk/device_data.tar")
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
                print("current zip file: {}".format(file_path))
                # 解压缩包
                zfile = zipfile.ZipFile(file_path)
                zfile.extractall(data_dir)
                for file_name in os.listdir(data_dir):
                    if file_name == "auto_device_info.json":
                        continue
                    if file_name.split(".")[-1] != "json":
                        continue
                    full_path = os.path.join(data_dir, file_name)
                    if os.path.isfile(full_path):
                        # 处理文件
                        print("current json file: {}".format(full_path))
                        with open(full_path) as f:
                            device_info = json.load(f)
                        print(device_info)
                        
                        os.remove(full_path)
                    else:
                        pass  # 递归处理子文件夹
                    
                
    