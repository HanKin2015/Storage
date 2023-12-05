# -*- coding: utf-8 -*-
"""
文 件 名: ssh_exec_command4.py
文件描述: 上传sh文件并执行返回结果
备    注: 
作    者: HanKin
创建日期: 2023.12.05
修改日期：2023.12.05

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

# 创建SFTP客户端对象
# 建立一个加密的管道
transport = paramiko.Transport(ip, port)
# 建立连接
transport.connect(username=user, password=password)
# 建立一个sftp客户端对象，通过ssh transport操作远程文件
sftp_client = paramiko.SFTPClient.from_transport(transport)

# 上传sh文件
sftp_client.put("./get_vm_runtime", "/stmp/get_vm_runtime")

# 执行命令并获取返回结果
command = 'chmod +x /stmp/get_vm_runtime'
stdin, stdout, stderr = client.exec_command(command)
command = 'dos2unix /stmp/get_vm_runtime'
stdin, stdout, stderr = client.exec_command(command)
command = '/stmp/get_vm_runtime win130001 test'
stdin, stdout, stderr = client.exec_command(command)
output = stdout.read().decode('utf-8')
error = stderr.read().decode('utf-8')

# 关闭SSH连接
client.close()
transport.close()

# 输出结果
print('Output:', output)
print('Error:', error)

# 对返回值进行处理
print(type(output)) # <class 'str'>
my_str = "[1, 2, 3, 4]"
my_lst = eval(my_str)
print(my_lst)       # [1, 2, 3, 4]
my_str = '{"x": 1, "y": 2}'
my_lst = eval(my_str)
print(my_lst)       # {'x': 1, 'y': 2}

output = output.replace("false", "0")
output = output.replace("null", "0")
result = eval(output)
print(type(result))                 # <class 'list'>
if len(result) != 1:
    print("result size is not one, {}".format(len(result)))
    raise Exception("-1")

json_obj = result[0]
print(type(json_obj))               # <class 'dict'>
print(json_obj.get("osType", ""))   # win1364

