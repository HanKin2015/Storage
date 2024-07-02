# -*- coding: utf-8 -*-
"""
文 件 名: threading_example.py
文件描述: 多线程
备    注：windows系统也是可以并发的
作    者: HanKin
创建日期: 2024.07.02
修改日期：2024.07.02
Copyright (c) 2024 HanKin. All rights reserved.
"""
import threading
import time

# 定义线程要运行的函数
def thread_function(name, delay):
    count = 5
    while count:
        print(f"线程 {name} 正在运行...")
        time.sleep(delay)
        count -= 1

def main():
    # 创建线程列表
    threads = []
     
    # 创建并启动线程
    for i in range(3):  # 创建3个线程
        t = threading.Thread(target=thread_function, args=("线程{}".format(i), i))
        threads.append(t)
        t.start()
     
    # 等待所有线程完成
    for t in threads:
        t.join()
     
    print("所有线程都已结束。")

if __name__ == '__main__':
    start_time = time.time()

    main()
    
    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))