# -*- coding: utf-8 -*-
"""
文 件 名: test_server_state.py
文件描述: 测试服务器状态
备    注: 
作    者: HanKin
创建日期: 2024.03.12
修改日期：2024.03.12

Copyright (c) 2024 HanKin. All rights reserved.
"""
import json
import requests

def upload_total():
    """测试分析平台服务器
    """
    try:
        filepath = "toolTotals.json"
        with open(filepath, "r", encoding="utf-8") as f:
            data = json.load(f)
        res = requests.post(url="http://xx.xx.xx.xx:8001/totals", json=data, timeout=1)
        if res.text:
            print(res.text)
            with open(filepath, "w", encoding="utf-8") as f:
                f.write("{}")
        print("success")
        return True
    except Exception as err:
        # failed, ('Connection aborted.', TimeoutError(10060, '由于连接方在一段时间后没有正确答复或连接的主机没有反应，连接尝试失败。', None, 10060, None)
        print("failed, {}".format(err))
        return False

def test_flask_local_server():
    """测试本地服务器平台
    """
    try:
        res = requests.post(url="http://xx.xx.xx.xx:8001/hello_ip", json=None, timeout=1)
        if res.text:
            print(res.text)
        print("success")
        return True
    except Exception as err:
        print("failed, {}".format(err))
        return False

def test_flask_server():
    """测试数据上传服务器平台
    """
    try:
        res = requests.post(url="http://xx.xx.xx.xx:4433/hello_real_ip", json=None, timeout=1)
        if res.text:
            print(res.text)
        print("success")
        return True
    except Exception as err:
        print("failed, {}".format(err))
        return False

if __name__ == '__main__':
    upload_total()
    test_flask_local_server()
    test_flask_server()
    test_real_ip()
    test_client_ip()