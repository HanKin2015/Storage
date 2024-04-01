# -*- coding: utf-8 -*-
"""
文 件 名: ip_address_location.py
文件描述: ip地址归属地
作    者: HanKin
创建日期: 2024.03.21
修改日期：2024.03.21

Copyright (c) 2024 HanKin. All rights reserved.
"""
import requests
import socket

def get_ip_location(ip_address):
    url = f"http://ipinfo.io/{ip_address}/json"
    response = requests.get(url)
    data = response.json()
    return data

ip_address = "58.20.54.211"  # 你要查询的IP地址
location = get_ip_location(ip_address)
print(location)


def get_local_ip():
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    return ip_address

local_ip = get_local_ip()
print(local_ip)

def get_public_ip():
    response = requests.get('https://api.ipify.org?format=json')
    data = response.json()
    return data['ip']

public_ip = get_public_ip()
print(public_ip)


import geoip2.database

# 用于查询 IP 地址的地理位置信息的数据库文件路径
database_path = '/path/to/GeoLite2-City.mmdb'

# 创建一个 Reader 对象，用于查询 IP 地址的地理位置信息
reader = geoip2.database.Reader(database_path)

# 查询 IP 地址的地理位置信息
response = reader.city('8.8.8.8')

# 输出查询结果
print(response.country.name)
print(response.city.name)
print(response.postal.code)
print(response.location.latitude, response.location.longitude)

# 记得关闭 Reader 对象
reader.close()