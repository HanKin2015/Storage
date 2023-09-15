# -*- coding: utf-8 -*-
"""
文 件 名: ThreadPoolExecutor_example2.py
文件描述: 线程池
备    注：另外一种写法，以及使用threading.Lock进行加锁，这样写有问题
作    者: HanKin
创建日期: 2023.09.15
修改日期：2023.09.15
Copyright (c) 2023 HanKin. All rights reserved.
"""
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
import threading

THREAD_NUM = 64

def test(index, lock):
    with lock:
        print(index)
        time.sleep(5)
        return index

def main():
    lock = threading.Lock()
    with ThreadPoolExecutor(max_workers=THREAD_NUM) as pool:
        tasks = [pool.submit(test, i, lock) for i in range(5)]
        print(tasks)
        for task in as_completed(tasks):
            index = task.result()
            print("done {}".format(index))
    return

if __name__ == '__main__':
    start_time = time.time()

    main()
    
    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
