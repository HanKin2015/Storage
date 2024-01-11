# -*- coding: utf-8 -*-
"""
文 件 名: paramiko_example.py
文件描述: 使用paramiko库远程连接
作    者: HanKin
创建日期: 2023.09.07
修改日期：2023.09.07

Copyright (c) 2023 HanKin. All rights reserved.
"""

from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5 as Cipher_pkcs1_v1_5
import os
import paramiko
import time
import logging
import sys
import retrying
import traceback
import base64
import re

# 项目根目录,拼接路径时"\\"常用于绝对路径，使用"/"可以不加转义符"\"，综上所述"\\"或者"/"都可以
basedir = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))
def get_logger():
    logger = logging.getLogger('patrol')
    # 指定logger输出格式
    formatter = logging.Formatter('%(asctime)s %(name)s %(filename)s %(lineno)s %(levelname)-4s: %(message)s')
    # 文件日志
    log_file = os.path.join(basedir, 'patrol.log')
    print('log_file: {}'.format(log_file))
    file_handler = logging.FileHandler(log_file, encoding="utf-8")
    # 指定输出格式
    file_handler.setFormatter(formatter)
    # 为logger添加的日志处理器
    logger.addHandler(file_handler)

    # 控制台日志
    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.formatter = formatter  # 也可以直接给formatter赋值
    logger.addHandler(console_handler)

    # 指定日志的最低输出级别
    logger.setLevel(logging.INFO)
    return logger

logger = get_logger()
class ConnectHost:

    def __init__(self, user, ip, password, port, flag=False):
        self.ip = ip
        self.user = user
        self.original_password = password
        # 获取RSA解密后的明文密码
        if flag:
            self.password = self.original_password
        else:
            self.password = self.original_password + ConnectHost.gen()
        self.port = port
        self.ssh_client = None
        self.sftp_client = None

    # RSA算法解密有关密码后缀的密文
    @staticmethod
    def gen():
        """仅仅是解析出了后缀密码拼接到原密码上面
        """
        key_file = os.path.join(basedir, "key.pem")
        input_file = os.path.join(basedir, "backend.data")
        with open(input_file, "r") as f:
            cipher_text = f.read()
        with open(key_file, "r") as f:
            key = f.read()
            rsakey = RSA.importKey(key)
            cipher = Cipher_pkcs1_v1_5.new(rsakey)
            text = cipher.decrypt(base64.b64decode(cipher_text),"ERROR")
        text = text.decode()
        print(text)
        return text

    # sftp client
    def get_sftp_client(self):
        try:
            # 建立一个加密的管道
            transport = paramiko.Transport(self.ip, self.port)
            # 建立连接
            transport.connect(username=self.user, password=self.password)
            # 建立一个sftp客户端对象，通过ssh transport操作远程文件
            self.sftp_client = paramiko.SFTPClient.from_transport(transport)
        except:
            logger.info("sftp connect to {0}:{1} {2} failed.".format(self.ip, self.port, self.user))
            logger.error(traceback.format_exc())

    def put_file_to_remote(self, local_path, remote_path):
        try:
            if not self.sftp_client:
                self.get_sftp_client()
            self.sftp_client.put(local_path, remote_path)
        except:
            logger.info("put file {0} to {1}:{2}{3}  failed.".format(local_path, self.ip, self.port, remote_path))
            logger.error(traceback.format_exc())

    def get_file_from_remote(self, remote_path, local_path, callback=None):
        try:
            if not self.sftp_client:
                self.get_sftp_client()
            self.sftp_client.get(remote_path, local_path, callback=callback)
        except:
            logger.info("get file {0} from {1}:{2}{3} failed.".format(local_path, self.ip, self.port, remote_path))
            logger.error(traceback.format_exc())

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
            logger.info("ssh connect to {0}:{1} failed.".format(self.ip, self.port))
            logger.error(str(e))
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
                logger.error("self.ssh_client is None")
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
            logger.info("exe [ {0} ] at {1}:{2} failed.".format(cmd, self.ip, self.port))
            logger.error(traceback.format_exc())
            return None

    def __del__(self):
        if self.ssh_client:
            self.ssh_client.close()
        elif self.sftp_client:
            self.sftp_client.close()
        else:
            pass

def parse_vdc_version(vdc_version):
    vdc_info_res = vdc_version.split("\n")[:-1]
    vdc_info_res = [i.replace("\t", "  ") for i in vdc_info_res]
    format_version = re.search("\d\.\d\.\d+", vdc_info_res[0]).group() if re.search("\d\.\d\.\d+",
                                                                                    vdc_info_res[0]) else re.search(
        "\d\.\d",
        vdc_info_res[0]).group()
    print(format_version)

def test_return_value(connect_host):
    """测试执行命令后返回的结果就是在终端打印的结果
    """
    ret = connect_host.exec_command("/stmp/device_helper/devicehelper -l")
    print(ret)

def main():
    """主函数
    """

    connect_host = ConnectHost("admin", ip="10.123.123.123", password="xxxx", port=22, flag=True)
    test_return_value(connect_host)
    
    vdc_version = connect_host.exec_command("cat /html/appversion")
    parse_vdc_version(vdc_version)
    try:
        m = re.search(r'VDI(\d\.\d.\d)', vdc_version)
        version = int(m.group(1).replace(".", ""))
    except:
        print(traceback.format_exc())
        version = 123
    logger.info("vdc_version: {}".format(version))

def debug():
    """调试
    """

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
    