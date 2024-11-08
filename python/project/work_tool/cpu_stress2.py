# -*- coding: utf-8 -*-
"""
文 件 名: cpu_stress2.py
文件描述: cpu占用小程序
备    注: 计算密集型任务和休眠之间交替，以控制 CPU 的使用率
作    者: HanKin
创建日期: 2024.11.05
修改日期：2024.11.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
import multiprocessing
import time

def cpu_stress(target_usage):
    # 计算占用和休眠的时间比例
    work_time = target_usage / 100.0
    sleep_time = 1.0 - work_time

    while True:
        # 占用 CPU 的时间
        start_time = time.time()
        while (time.time() - start_time) < work_time:
            pass  # 占用 CPU

        # 休眠时间
        time.sleep(sleep_time)

if __name__ == "__main__":
    # 目标 CPU 使用率
    target_cpu_usage = 60  # 60%

    # 获取 CPU 核心数量
    num_cores = multiprocessing.cpu_count()
    print(f"Starting stress test on {num_cores} cores with target usage of {target_cpu_usage}%.")

    # 创建与 CPU 核心数量相同的进程
    processes = []
    for _ in range(num_cores):
        process = multiprocessing.Process(target=cpu_stress, args=(target_cpu_usage,))
        processes.append(process)
        process.start()

    # 等待所有进程完成（实际上它们不会完成，因为是无限循环）
    for process in processes:
        process.join()
