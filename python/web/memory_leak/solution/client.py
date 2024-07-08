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
    # 建立Telnet连接
    tn = telnetlib.Telnet('172.22.192.25', port=8029, timeout=10)
    
    # 将命令字符串编码为字节串
    command = 'your command here\n'.encode('utf-8')

    # 发送内容到远程主机
    tn.write(command)
     
    # 读取远程主机响应的内容
    #response = tn.read_very_eager()
    # 注意：read_very_eager() 可能不会返回所有数据，因为它不会等待数据到达
    # 你可能需要使用 read_until() 或其他 read 方法来更可靠地读取数据
    response = tn.read_some()  # 或者使用 tn.read_until(some_pattern.encode('utf-8'))
    print(response.decode('utf-8'))  # 使用相同的编码来解码响应
     
    # 关闭Telnet连接（这个影响长连接，但是注释掉后也不是长连接）
    #tn.close()
    time.sleep(10)
 
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
    #time.sleep(20)

if __name__ == '__main__':
    test_flask_server()
    #telnet_example()
    #thread_function(1, 1)