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

# 创建SSH客户端对象并建立连接
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect("110.170.110.170", 22, "admin", "hello@999")

# 执行命令并获取返回结果
command = 'chmod +x /home/admin/test.sh'
stdin, stdout, stderr = client.exec_command(command)
# 直接使用sudo命令会报错sudo: no tty present and no askpass program specified
# -S, --stdin    read password from standard input
command = 'echo hello@999 | sudo -S /home/admin/test.sh'
stdin, stdout, stderr = client.exec_command(command)
output = stdout.read().decode('utf-8')
error = stderr.read().decode('utf-8')

# 嵌套执行命令（需要输入密码可借助sshpass工具）
command = "echo hello@999 | sudo -S util debug -k 9SN1234567 -o | awk 'NR == 2{print $5}'"
stdin, stdout, stderr = client.exec_command(command)
output = stdout.read().decode('utf-8')
error = stderr.read().decode('utf-8')
addr = output
addr = addr.replace("\n", "")   # 老是没有考虑到有换行符的存在
command = 'adb connect {}'.format(addr)
stdin, stdout, stderr = client.exec_command(command)
command = "echo hello@999 | sudo -S adb -s {} shell /data/local/tmp/arm_binary -p /data/local/tmp/pp".format(addr)
print(command)
stdin, stdout, stderr = client.exec_command(command)
output = stdout.read().decode('utf-8')
error = stderr.read().decode('utf-8')

# 关闭SSH连接
client.close()

# 输出结果
print('Output:', output)
print('Error:', error)
