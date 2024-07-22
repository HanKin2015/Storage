# -*- coding: utf-8 -*-
"""
文 件 名: test_chromedriver.py
文件描述: 新版本使用方式有啥变化
备    注: https://www.cnblogs.com/lxmtx/p/17945756
作    者: HanKin
创建日期: 2024.07.22
修改日期：2024.07.22

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
 
options = webdriver.ChromeOptions()
service = Service(executable_path=r"C:\Program Files\Google\Chrome\Application\chromedriver.exe")
driver = webdriver.Chrome(service=service, options=options)
driver.get("https://www.baidu.com/")
 
# 最大化浏览器
driver.maximize_window()
time.sleep(3)
driver.close()