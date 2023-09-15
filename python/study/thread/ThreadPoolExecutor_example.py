# -*- coding: utf-8 -*-
"""
文 件 名: ThreadPoolExecutor_example.py
文件描述: 线程池
备    注：windows系统也是可以并发的
作    者: HanKin
创建日期: 2023.09.15
修改日期：2023.09.15
Copyright (c) 2023 HanKin. All rights reserved.
"""
import os, re, time, datetime
from concurrent.futures import ThreadPoolExecutor

THREAD_NUM = 64

def test(index):
    print(index)
    time.sleep(10)
    return index

def main():
    tasks = []
    with ThreadPoolExecutor(max_workers=THREAD_NUM) as pool:
        for i in range(10):
            task = pool.submit(test, i)
            tasks.append(task)
    
    for task in tasks:
        index = task.result()
        print("done {}".format(index))
    return

if __name__ == '__main__':
    start_time = time.time()

    main()
    
    end_time = time.time()
    logger.info('process spend {} s.'.format(round(end_time - start_time, 3)))