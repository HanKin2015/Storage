# -*- coding: utf-8 -*-
"""
Created on Sat Sep 19 13:18:20 2020

@author: Administrator
"""

import time
from selenium import webdriver
import pandas as pd

chrome_path = r"C:/Program Files (x86)/Google/Chrome/Application/chromedriver.exe"
driver = webdriver.Chrome(chrome_path)
url = 'http://www.cszjxx.net/floorinfo/202004160830'

page = driver.get(url)
time.sleep(2)


elem = driver.find_element_by_class_name('td.hs_zk')
time.sleep(2)
print(elem)
elem.click()
time.sleep(2)
df = pd.read_html(driver.page_source)
pd.DataFrame(df).to_csv('./t.csv', index=False)

