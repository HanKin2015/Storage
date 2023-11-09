# -*- coding: utf-8 -*-
"""
文 件 名: get_ip_mac.py
文件描述: 获取系统的ip和mac地址
作    者: HanKin
创建日期: 2023.11.06
修改日期：2023.11.09

Copyright (c) 2023 HanKin. All rights reserved.
"""
import uuid
def get_mac_address1():
    """
    获取本机MAC地址
    :return mac: 本机MAC地址
    """
    mac = uuid.UUID(int=uuid.getnode()).hex[-12:]
    return ":".join([mac[e:e+2] for e in range(0, 11, 2)])

import subprocess

def get_mac_address2():
    """
    获取本机MAC地址(在Linux和Mac OS X系统上有效)
    :return mac: 本机MAC地址
    """
    try:
        output = subprocess.check_output(['ifconfig'])
        output = output.decode('utf-8')
        lines = output.split('\n')
        for line in lines:
            if 'ether' in line:
                mac = line.split('ether')[1].strip().split()[0]
                return mac
    except subprocess.CalledProcessError:
        pass

    return None
    
def get_mac_address3():
    """
    获取本机MAC地址
    :return mac: 本机MAC地址
    """
    try:
        output = subprocess.check_output(['ipconfig', '/all'])
        output = output.decode('gbk')
        lines = output.split('\n')
        for line in lines:
            if 'Physical Address' in line:
                mac = line.split(':')[1].strip().replace('-', ':')
                return mac
            elif '虚拟网卡' in line:
                mac = line.split(':')[1].strip().replace('-', ':')
                return mac
    except subprocess.CalledProcessError:
        pass

    return None

# 部分PC安装netifaces失败，说依赖libffi库，安装的时候有出现error: Microsoft Visual C++ 14.0 or greater is required.
#import netifaces
#def get_mac_address4():
#    """
#    获取本机MAC地址
#    :return mac: 本机MAC地址
#    """
#    for interface in netifaces.interfaces():
#        try:
#            mac = netifaces.ifaddresses(interface)[netifaces.AF_LINK][0]['addr']
#            return mac
#        except KeyError:
#            pass
#
#    return None

import psutil
def get_mac_address5():
    """
    获取本机MAC地址
    :return mac: 本机MAC地址
    """
    for interface, addrs in psutil.net_if_addrs().items():
        for addr in addrs:
            if addr.family == psutil.AF_LINK:
                mac = addr.address
                return mac

    return None

import win32com.client
def get_mac_address6():
    """
    获取本机MAC地址
    :return mac: 本机MAC地址
    """
    mac = None
    try:
        wmi = win32com.client.GetObject("winmgmts:")
        adapters = wmi.ExecQuery("SELECT MACAddress FROM Win32_NetworkAdapter WHERE PhysicalAdapter=True")
        for adapter in adapters:
            mac = adapter.MACAddress
            break
    except Exception as e:
        pass

    return mac

def get_all_mac_address():
    """
    获取本机所有MAC地址
    :return mac: 本机MAC地址
    """
    mac_list = []
    for interface, addrs in psutil.net_if_addrs().items():
        for addr in addrs:
            print(addr.family, addr.address)
            if addr.family == psutil.AF_LINK:
                mac = addr.address
                mac = mac.replace("-", ":")
                mac_list.append(mac)

    return mac_list

import socket
def get_local_ip():
    """
    获取本机IP地址
    :return ip: 本机IP地址
    """
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect(('8.8.8.8', 80))
    ip = s.getsockname()[0]
    s.close()
    return ip

import time
if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    print("get_mac_address1: {}".format(get_mac_address1()))
    #print("get_mac_address2: {}".format(get_mac_address2()))
    print("get_mac_address3: {}".format(get_mac_address3()))
    #print("get_mac_address4: {}".format(get_mac_address4()))
    print("get_mac_address5: {}".format(get_mac_address5()))
    print("get_mac_address6: {}".format(get_mac_address6()))
    print("get_local_ip: {}".format(get_local_ip()))
    print("get_all_mac_address: {}".format(get_all_mac_address()))

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

r"""
物理PC：98-EE-CB-6F-2A-70
(base) C:\Users\test\Desktop>PYTHON K.PY
******** starting ********
get_mac_address1: 98:ee:cb:6f:2a:70
get_mac_address3: None
get_mac_address5: 00-FF-D0-E7-52-99
get_mac_address6: 98:EE:CB:6F:2A:70
get_local_ip: 172.22.16.121
process spend 0.158 s.

虚拟机：FE-FC-FE-24-10-4F
(base) D:\Users\User\Desktop>python k.py
******** starting ********
get_mac_address1: c1:d1:4c:22:17:93
get_mac_address3: None
get_mac_address4:
get_mac_address5: FE-FC-FE-24-10-4F
get_mac_address6: FE:FC:FE:24:10:4F
get_local_ip: 172.22.64.246
process spend 0.521 s.

会发现第六种方法是正确的，然鹅如果插上一个无线wifi，则会获取无线WiFi地址：
我自己的物理PC并没有什么变化，那如果我是使用无线wifi的，结果你给我获取了有线网卡的mac地址。
(base) C:\Users\test\Desktop>python k.py
******** starting ********
get_mac_address1: 98:ee:cb:6f:2a:70
get_mac_address3: None
get_mac_address5: 00-FF-D0-E7-52-99
get_mac_address6: 98:EE:CB:6F:2A:70
get_local_ip: 172.22.16.121
process spend 0.19 s.
"""