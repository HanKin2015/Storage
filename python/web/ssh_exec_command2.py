# -*- coding: utf-8 -*-
"""
文 件 名: ssh_exec_command2.py
文件描述: 高级点
作    者: HanKin
创建日期: 2023.11.17
修改日期：2023.11.17

Copyright (c) 2023 HanKin. All rights reserved.
"""
import paramiko

# 创建SSH客户端对象并建立连接
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect("110.170.110.170", 22, "admin", "hello@123")

# 执行命令并获取返回结果
command = 'chmod +x /home/admin/test.sh'
stdin, stdout, stderr = client.exec_command(command)
command = 'sudo /home/admin/test.sh'    
stdin, stdout, stderr = client.exec_command(command)
output = stdout.read().decode('utf-8')
error = stderr.read().decode('utf-8')

# 关闭SSH连接
client.close()

# 输出结果
print('Output:', output)
print('Error:', error)
"""
错误的情况：
Output:
Error: cat: /etc/appversion: No such file or directory

正常情况：
Output: 00:01.0 ISA bridge: Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]
00:01.1 IDE interface: Intel Corporation 82371SB PIIX3 IDE [Natoma/Triton II]
00:01.2 USB controller: Intel Corporation 82371SB PIIX3 USB [Natoma/Triton II] (rev 01)

Error:
"""
