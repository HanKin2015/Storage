# -*- coding: utf-8 -*-
"""
Created on Sat Sep 19 16:27:30 2020

@author: Administrator
"""

from selenium import webdriver
import pandas as pd
import time

url = "http://www.cszjxx.net/floorinfo/202004160830" #世界大学排名
#为selenium配置Chrome浏览器
options = webdriver.ChromeOptions()
options.add_argument('--headless')
options.add_argument('--no-sandbox')
options.add_argument('--disable-gpu')#配置无界面模式 
options.add_argument('--disable-dev-shm-usage')
driver = webdriver.Chrome(executable_path='C:/Program Files (x86)/Google/Chrome/Application/chromedriver.exe', chrome_options=options)
page = driver.get(url)
time.sleep(3)#笨方法睡3秒等待网页加载
#获取源码,解析出table
html = driver.page_source
tables = pd.read_html(html) #返回一个List,里面封装的是Dataframe
#tables = pd.read_html(url) #如果是静态网站可以直接通过url搞定
pd.DataFrame(tables).to_csv('./tt.csv', index=False)