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

ret = driver.find_element_by_class_name('hs_zk')
print(ret.text)
print(type(ret))
print(ret)

print(ret.tag_name, ret.is_enabled(), ret.is_displayed())
print(ret.get_attribute('innerText'))
print(ret.get_attribute('innerHTML'))
print(ret.get_attribute('textContent'))
print(ret.get_attribute('style'))
driver.execute_script("arguments[0].style.display = 'block';", ret)
print(ret.get_attribute('style'), ret.is_displayed())
#ret.click()
#ElementNotInteractableException: element not interactable
t = driver.find_element_by_xpath(".//*[@class='hs_table']/table/tbody/tr[2]/td[8]")
print(t)
print(t.text)


driver.execute_script('arguments[0].click();', ret)
print()
time.sleep(5)
#ret = driver.find_element_by_id('loadertr_KF2004200091_2')
#print(ret)
#driver.refresh()
#p = driver.find_element_by_link_text('点击加载更多')
#print('p=', p)
#t = driver.find_element_by_xpath(".//*[@id='loadertr_KF2004200091_2']/td[1]")
#print(t.is_displayed())
t = driver.find_elements_by_xpath(".//*[@id='hs_table2_KF2004200091']/table/tbody/tr")
print(len(t))
t = driver.find_element_by_xpath(".//*[@id='hs_table2_KF2004200091']/table/tbody/tr[td[text()='点击加载更多']]/td[text()='点击加载更多']")

print(t.get_attribute('innerText'))
driver.execute_script('arguments[0].click();', t)



'''
div = driver.find_element_by_class_name('hs_table1')
time.sleep(2)
print(div.get_attribute('style'))
driver.execute_script("arguments[0].style.display = 'block';", div)
print(div.get_attribute('style'))
#elem.click()
time.sleep(2)
print(driver.page_source)
time.sleep(2)
df = pd.read_html(driver.page_source)
pd.DataFrame(df).to_csv('./t.csv', index=False)
'''
