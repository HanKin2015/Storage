# -*- coding: utf-8 -*-
"""
文 件 名: client.py
文件描述: 客户端测试flask服务端
备    注: 
作    者: HanKin
创建日期: 2024.06.28
修改日期：2024.06.28

Copyright (c) 2024 HanKin. All rights reserved.
"""
import json
import requests
import time
import telnetlib
import threading

def test_flask_server():
    try:
        res = requests.post(url="http://172.22.192.25:8029/hello_flask", timeout=1)
        if res.text:
            print(res.text)
        res = requests.get(url="http://172.22.192.25:8029/hello_world?name=hejian", timeout=1)
        if res.text:
            print(res.text)
        res = requests.post(url="http://172.22.192.25:8029/login", timeout=1)
        if res.text:
            print(res.text)

        #time.sleep(10)
        
        print("success")
        return True
    except Exception as err:
        # failed, ('Connection aborted.', TimeoutError(10060, '由于连接方在一段时间后没有正确答复或连接的主机没有反应，连接尝试失败。', None, 10060, None)
        print("failed, {}".format(err))
        return False

# 定义线程要运行的函数
def thread_function(name, delay):
    telnetlib.Telnet('172.22.192.25', port=8029, timeout=10)
 
def telnet_example():
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
    time.sleep(10)

if __name__ == '__main__':
    test_flask_server()
    #telnet_example()