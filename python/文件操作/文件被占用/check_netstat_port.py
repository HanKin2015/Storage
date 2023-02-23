# -*- coding: utf-8 -*-
"""
文 件 名: check_netstat_port.py
文件描述: python找到端口占用，并杀死进程
备    注: https://www.cnblogs.com/pure-peace/p/12702099.html
作    者: HanKin
创建日期: 2023.02.22
修改日期：2023.02.22

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import os
import sys
import subprocess
import win32api
import ctypes
  
def main():
    """主函数
    """

    with os.popen('netstat -aon|findstr "443"') as r:
        ret = r.read()
        print(type(ret), len(ret))
        print(ret)
    
    result = []
    for line in ret.split('\n'):
        temp = [i for i in line.split(' ') if i != '']
        if len(temp) > 4:
            result.append({'pid': temp[4], 'address': temp[1], 'state': temp[3]})
    print(result)

    # 方法一
    result = os.popen("taskkill -pid 进程pid -f")
    
    # 方法二
    handle = win32api.OpenProcess(1, False, "进程pid") # 获取进程句柄（pid类型为int！）
    win32api.TerminateProcess(handle, 0) # 杀了它
    win32api.CloseHandle(handle) # 关闭

    # 方法三
    handle = ctypes.windll.kernel32.OpenProcess(1, False, "进程pid") # 同上（pid类型为int！）
    ctypes.windll.kernel32.TerminateProcess(handle, -1)
    ctypes.windll.kernel32.CloseHandle(handle)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))