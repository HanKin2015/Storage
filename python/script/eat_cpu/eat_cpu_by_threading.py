# -*- coding: utf-8 -*-
"""
文 件 名: eat_cpu_by_threading.py
文件描述: cpu占用小程序
备    注: pyinstaller打包后还是存在内存泄露
作    者: HanKin
创建日期: 2024.11.05
修改日期：2024.11.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
import threading
import time

def cpu_stress(target_usage):
    work_time = target_usage / 100.0
    sleep_time = 1.0 - work_time

    while True:
        start_time = time.time()
        while (time.time() - start_time) < work_time:
            pass  # 占用 CPU
        time.sleep(sleep_time)

if __name__ == "__main__":
    target_cpu_usage = 20  # 20%
    num_threads = 4  # 可以根据需要调整线程数量

    threads = []
    for _ in range(num_threads):
        thread = threading.Thread(target=cpu_stress, args=(target_cpu_usage,))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()
