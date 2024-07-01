# -*- coding: utf-8 -*-
"""
文 件 名: process_ananlysis.py
文件描述: 进程分析（周末两天的时间进程数量从160涨到了384，很奇怪罪魁祸首SogouComMgr.exe）
备    注: 杀死进程树SGTool.exe即可
作    者: HanKin
创建日期: 2024.06.17
修改日期：2024.06.17

Copyright (c) 2024 HanKin. All rights reserved.
"""
import psutil
import time
import os

def processes_analysis():
    """进程分析
    """
    current_pid = os.getpid()
    print(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - -------- 开始分析进程 --------')

    # 获取当前所有进程的快照
    processes = psutil.process_iter(['pid', 'name'])
    process_dict = {p.info['pid']: p.info['name'] for p in processes}
    print(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 当前存在进程数量: {len(process_dict)}')
    
    process_count_dict = dict()
    # 检查进程状态
    for pid, name in process_dict.items():
        if name not in process_count_dict:
            process_count_dict[name] = 1
        else:
            process_count_dict[name] += 1
    print(f'{time.strftime("%Y-%m-%d %H:%M:%S")} [{current_pid}] - 当前唯一进程数量: {len(process_count_dict)}')
    
    process_top_dict = dict(sorted(process_count_dict.items(), key=lambda item: item[1], reverse=True))
    top_threshold = 0
    for name, count in process_top_dict.items():
        print(name, ":", count);
        top_threshold += 1
        if top_threshold > 10:
            break

if __name__ == '__main__':
    processes_analysis()
