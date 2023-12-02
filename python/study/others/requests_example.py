# -*- coding: utf-8 -*-
"""
文 件 名: requests_example.py
文件描述: HTTP协议应用
作    者: HanKin
创建日期: 2023.12.02
修改日期：2023.12.02

Copyright (c) 2023 HanKin. All rights reserved.
"""
import requests
response = requests.get("https://www.example.com")
print(response.text)