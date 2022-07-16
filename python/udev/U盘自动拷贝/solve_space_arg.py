# -*- coding: utf-8 -*-
"""
文 件 名: solve_space_arg.py
文件描述: 解决cmd命令遇见空格文件夹路径问题
作    者: HanKin
创建日期: 2022.05.24
修改日期：2022.04.08

创建文件夹: y e s

[root@ubuntu0006:/media/hankin/vdb/study/udev] #python solve_space_arg.py -u y\ e\ s/
Namespace(data_path='./data/', upan_path='y e s/')
sh: 1: cd: can't cd to y
cmd: cd y e s/, 执行失败

(base) D:\tmp>python solve_space_arg.py -u "y e s"
Namespace(data_path='./data/', upan_path='y e s')
cmd: cd y e s, 执行成功

结论: linux端解决不了

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import argparse
import logging
import hashlib

data_path = './data/'
upan_path = 'E'

def argument_parser():
    """参数解析

    命令行参数解析

    Parameters
    ----------
    """
    
    parser = argparse.ArgumentParser(description='欢迎使用U盘自动写入文件脚本')
    #type是要传入的参数的数据类型  help是该参数的提示信息
    parser.add_argument('-u', dest='upan_path', default='E', type=str, help='U盘路径')
    parser.add_argument('-d', dest='data_path', default='./data/', type=str, help='数据路径')

    args = parser.parse_args()

    #获得传入的参数
    print(args)
    
    global upan_path, data_path
    upan_path = args.upan_path
    data_path = args.data_path
    
argument_parser()

cmd = 'cd {}'.format(upan_path)
ret = os.system(cmd)
if ret != 0:
    print('cmd: {}, 执行失败'.format(cmd))
else:
    print('cmd: {}, 执行成功'.format(cmd))