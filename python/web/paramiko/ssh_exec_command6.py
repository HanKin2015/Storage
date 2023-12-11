# -*- coding: utf-8 -*-
"""
文 件 名: ssh_exec_command3.py
文件描述: 嵌套执行命令
备    注: 注意安卓系统一定需要在特定的目录下面执行脚本，因此需要写入绝对路径
作    者: HanKin
创建日期: 2023.11.20
修改日期：2023.11.20

Copyright (c) 2023 HanKin. All rights reserved.
"""
import paramiko
import re
import time
from Crypto.PublicKey import RSA
import Crypto

print(Crypto.__version__)

ip       = "10.70.10.70"
port     = 22
user     = "admin"
password = "hello@123sangfornetwork"
sshpass_filename = "/stmp/device_helper_info/sshpass"
box_sn   = "7CR3220345"

# 创建SSH客户端对象并建立连接
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect(ip, port, user, password)

for i in range(50):
    # 执行命令并获取返回结果
    command = "echo %s |sudo -S adesk_debug.sh -s %s" % (password, box_sn)
    stdin, stdout, stderr = client.exec_command(command)
    output = stdout.read().decode('utf-8')
    error = stderr.read().decode('utf-8')
    port = re.search(r"ssh root@localhost -p (.*)", output).group(1)
    print("port {}".format(port))

    # 嵌套执行命令（需要输入密码可借助sshpass工具）
    command = "echo %s | sudo -S %s -p 'greatvdix862015' ssh -o StrictHostKeyChecking=no root@localhost -p %s" % (
              password, sshpass_filename, port)
    stdin, stdout, stderr = client.exec_command(command)
    output = stdout.read().decode('utf-8')
    error = stderr.read().decode('utf-8')
    time.sleep(2)

# 关闭SSH连接
client.close()

# 输出结果
print('Output:', output)
print('Error:', error)
