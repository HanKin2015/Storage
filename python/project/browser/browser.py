# -*- coding: utf-8 -*- 

'''
from selenium import webdriver 

chromedriver_path = r"C:/Program Files (x86)/Google/Chrome/Application/chromedriver.exe"

driver = webdriver.Chrome(chromedriver_path)    #打开浏览器
#driver = webdriver.Firefox()

driver.maximize_window() #最大化窗口

url = "https://www.baidu.com"
driver.get(url) #打开网页
time.sleep(2)   #时刻需要睡眠等待一下
'''

import webbrowser

webbrowser.open("https://www.baidu.com")