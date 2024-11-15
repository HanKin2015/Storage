# -*- coding: utf-8 -*-
"""
文 件 名: eat_cpu_by_multiprocessing1.py
文件描述: cpu占用小程序
备    注: 这个根据cpu数量进行占用
作    者: HanKin
创建日期: 2024.11.05
修改日期：2024.11.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
import multiprocessing
import time

def cpu_stress():
    while True:
        pass  # 无限循环，占用 CPU

if __name__ == "__main__":
    # 获取 CPU 核心数量
    num_cores = multiprocessing.cpu_count()
    print(f"Starting stress test on {num_cores} cores.")
    
    # 创建与 CPU 核心数量相同的进程
    processes = []
    for _ in range(1):
        process = multiprocessing.Process(target=cpu_stress)
        processes.append(process)
        process.start()

    # 等待所有进程完成（实际上它们不会完成，因为是无限循环）
    for process in processes:
        process.join()