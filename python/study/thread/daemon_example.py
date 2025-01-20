# -*- coding: utf-8 -*-
"""
文 件 名: daemon_example.py
文件描述: 守护线程来实现类似于分离线程的效果
作    者: HanKin
备    注: 
创建日期: 2025.01.20
修改日期：2025.01.20

Copyright (c) 2025 HanKin. All rights reserved.
"""
import threading
import time

# 定义要在线程中执行的函数
def worker_function():
    while True:
        print("守护线程正在运行...")
        time.sleep(1)

# 创建线程
daemon_thread = threading.Thread(target=worker_function)
daemon_thread.daemon = True  # 设置为守护线程

# 启动线程
daemon_thread.start()

# 主线程执行其他任务
for i in range(5):
    print(f"主线程正在执行... {i}")
    time.sleep(0.5)

print("主线程结束，守护线程将被终止。")
