# -*- coding: utf-8 -*-
"""
文 件 名: record_process_exit_time.py
文件描述: 记录进程退出时间
备    注: 
作    者: HanKin
创建日期: 2024.06.13
修改日期：2024.06.13

Copyright (c) 2024 HanKin. All rights reserved.
"""
import psutil
import time
import os

def monitor_processes():
    """监控进程
    """
    update_snapshot_time = 0
    current_pid = os.getpid()
    if os.path.exists('process_log.txt'):
        with open('process_log.txt', 'a') as f:
            f.write('\n')
    with open('process_log.txt', 'a') as f:
        f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - -------- 开始监控进程 --------\n')

    while True:
        # 获取当前所有进程的快照，半分钟更新一次快照
        if update_snapshot_time % 30 == 0:
            processes = psutil.process_iter(['pid', 'name'])
            process_dict = {p.info['pid']: p.info['name'] for p in processes}
            with open('process_log.txt', 'a') as f:
                f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 当前存在进程数量: {len(process_dict)}\n')
            print(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}]')
    
        # 检查进程是否关闭
        for pid in process_dict.copy():
            if not psutil.pid_exists(pid):
                process_name = process_dict.pop(pid)
                # 记录进程关闭的时间和名称
                with open('process_log.txt', 'a') as f:
                    f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 进程关闭: {process_name}\n')

        # 每隔一段时间检查一次进程状态
        time.sleep(1)
        update_snapshot_time += 1
        if os.path.exists('close_process'):
            break
    
    with open('process_log.txt', 'a') as f:
        f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - -------- 结束监控进程 --------\n')

def monitor_processes2():
    """监控进程
    """
    current_pid = os.getpid()
    if os.path.exists('process_log.txt'):
        with open('process_log.txt', 'a') as f:
            f.write('\n')
    with open('process_log.txt', 'a') as f:
        f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - -------- 开始监控进程 --------\n')

    # 获取当前所有进程的快照
    processes = psutil.process_iter(['pid', 'name'])
    last_process_dict = {p.info['pid']: p.info['name'] for p in processes}
    with open('process_log.txt', 'a') as f:
         f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 当前存在进程数量: {len(last_process_dict)}\n')
    is_update = True
    while True:
        # 获取当前所有进程的快照
        processes = psutil.process_iter(['pid', 'name'])
        process_dict = {p.info['pid']: p.info['name'] for p in processes}

        is_update = False
        union_process_dict = {**process_dict, **last_process_dict}
        # 检查进程状态
        for pid, name in union_process_dict.items():
            if pid in process_dict and pid not in last_process_dict:
                is_update = True
                # 记录进程关闭的时间和名称
                with open('process_log.txt', 'a') as f:
                    f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 进程打开: {name}\n')
            elif pid not in process_dict and pid in last_process_dict:
                is_update = True
                # 记录进程关闭的时间和名称
                with open('process_log.txt', 'a') as f:
                    f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 进程关闭: {name}\n')
        last_process_dict = process_dict
        if is_update:
            with open('process_log.txt', 'a') as f:
                f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 当前存在进程数量: {len(process_dict)}\n')
            print(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}]')

        # 每隔一段时间检查一次进程状态
        time.sleep(1)
        if os.path.exists('close_process'):
            break
    
    with open('process_log.txt', 'a') as f:
        f.write(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - -------- 结束监控进程 --------\n')

if __name__ == '__main__':
    monitor_processes2()
