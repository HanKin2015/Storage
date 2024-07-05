# -*- coding: utf-8 -*-
"""
文 件 名: telnet_example.py
文件描述: telnet命令创建多个长连接
备    注: 
作    者: HanKin
创建日期: 2024.06.28
修改日期：2024.06.28

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
import telnetlib
import threading
import time

# 创建telnet连接
tn = telnetlib.Telnet('121.46.130.154', port=8001, timeout=10)
print(1)
tn = telnetlib.Telnet('121.46.130.154', port=8001, timeout=10)
print(2)

# 定义线程要运行的函数
def thread_function(name, delay):
    os.system("C:\\Users\\Administrator\\AppData\\Roaming\\MobaXterm\\slash\\bin\\telnet.exe 121.46.130.154 8001")
 
# 创建线程列表
threads = []
 
# 创建并启动线程
for i in range(10):  # 创建3个线程
    t = threading.Thread(target=thread_function, args=("线程{}".format(i), i))
    threads.append(t)
    t.start()
 
# 等待所有线程完成
for t in threads:
    t.join()
 
print("所有线程都已结束。")

time.sleep(20)

# 关闭连接
#tn.close()