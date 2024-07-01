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

def test_flask_server():
    try:
        res = requests.post(url="http://172.22.192.25:8029/hello_flask", timeout=1)
        if res.text:
            print(res.text)
        print("success")
        return True
    except Exception as err:
        # failed, ('Connection aborted.', TimeoutError(10060, '由于连接方在一段时间后没有正确答复或连接的主机没有反应，连接尝试失败。', None, 10060, None)
        print("failed, {}".format(err))
        return False

def test_flask_server_by_socketio():
    try:
        res = requests.post(url="http://172.22.192.25:8080", timeout=1)
        if res.text:
            print(res.text)
        print("long connection success")
        
        res = requests.post(url="http://172.22.192.25:8029/hello_short_connection", timeout=1)
        if res.text:
            print(res.text)
        print("short connection success")
        return True
    except Exception as err:
        # failed, ('Connection aborted.', TimeoutError(10060, '由于连接方在一段时间后没有正确答复或连接的主机没有反应，连接尝试失败。', None, 10060, None)
        print("failed, {}".format(err))
        return False

if __name__ == '__main__':
    test_flask_server()