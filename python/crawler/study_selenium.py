# -*- coding: utf-8 -*-
"""
Created on Wed Sep 23 13:24:04 2020

@author: hankin
"""

from selenium import webdriver
import time

url = 'http://www.baidu.com'
chromedriver_path = r"C:/Program Files (x86)/Google/Chrome/Application/chromedriver.exe"
driver = webdriver.Chrome(executable_path=chromedriver_path)    # 打开浏览器
driver.implicitly_wait(10)
#webdriver.minimize_window() #最小化窗口
webdriver.maximize_window() #最大化窗口
driver.get(url) # 打开网页
time.sleep(2)   # 时刻需要睡眠等待一下
#driver.back()   # 返回上一页（右箭头）
#driver.forward()# 去下一页（左箭头）
#driver.refresh()# 刷新当前网页
element = driver.find_element_by_link_text(r'新闻')
print(element)
# .submit() 模拟键盘的回车键，但是没有鼠标悬浮因此不行
element.click()
time.sleep(2)
#driver.close()  # 关闭当前窗口，是最开始的，而不是新打开的新闻窗口
time.sleep(2)

# ==============================================
# window_size
# ==============================================
print(driver.get_window_size())
driver.set_window_size(800, 600)
print(driver.get_window_size())
time.sleep(2)

# ==============================================
# window_position
# ==============================================
print(driver.get_window_position())
driver.set_window_position(200,400)
print(driver.get_window_position())
time.sleep(2)

# ==============================================
# window_rect
# ==============================================
print(driver.get_window_rect())
driver.set_window_rect(x=10, y=20, width=1000, height=800)
print(driver.get_window_rect())
time.sleep(2)


driver.quit()   # 退出浏览器，清空临时文件












