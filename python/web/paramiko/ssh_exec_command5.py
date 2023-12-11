# -*- coding: utf-8 -*-
"""
文 件 名: ssh_exec_command5.py
文件描述: 判断两个文件是否一样
备    注: 
作    者: HanKin
创建日期: 2023.12.07
修改日期：2023.12.07

Copyright (c) 2023 HanKin. All rights reserved.
"""
import paramiko

ip       = "110.170.130.170"
port     = 22
user     = "admin"
password = "hello@999"

# 创建SSH客户端对象并建立连接
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect(ip, port, user, password)

# 执行命令并获取返回结果
command = 'md5sum /tmp/device_helper/effective_policy.xml.last'
stdin, stdout, stderr = client.exec_command(command)
output = stdout.read().decode('utf-8')
error = stderr.read().decode('utf-8')
if output == "":
    print("不存在此文件")
    command = 'cp /tmp/device_helper/effective_policy.xml /tmp/device_helper/effective_policy.xml.last'
    client.exec_command(command)
else:
    xml_last_md5 = output.split()[0]
    print(xml_last_md5)
    command = 'md5sum /tmp/device_helper/effective_policy.xml'
    stdin, stdout, stderr = client.exec_command(command)
    output = stdout.read().decode('utf-8')
    error = stderr.read().decode('utf-8')
    xml_md5 = output.split()[0]
    print(xml_md5)
    if xml_md5 == xml_last_md5:
        print("两个文件一样")
    else:
        print("两个文件不一样")

# 关闭SSH连接
client.close()
