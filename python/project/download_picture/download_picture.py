# -*- coding: utf-8 -*-
"""
Created on Thu Nov 19 19:33:48 2020

@author: hankin
"""

import time
from selenium import webdriver
import requests
 
# 图片网页规则
url_regex = [
        ["https://ss.netnr.com/wallpaper","a.list-group-item", 1]
        ]

#伪造浏览器访问
headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
        }

# 睡眠等待时间
sleep_time = 2
 
def download_picture(url, save_file_path):
    '''下载图片
    '''
    chromedriver_path = r"C:/Program Files (x86)/Google/Chrome/Application/chromedriver.exe"
    driver = webdriver.Chrome(chromedriver_path)    # 打开浏览器
    driver.maximize_window() # 最大化窗口
    #driver.set_window_size(1000,30000) # 这种方式抓取需要拉动滑滚条的页面内容不可取
    
    driver.get(url) # 打开网页
    time.sleep(sleep_time)   # 时刻需要睡眠等待一下

    # 滚动网页解锁更多的图片
    driver.execute_script("window.scrollBy(0,30000)")
    time.sleep(sleep_time*10)

    div_elements = driver.find_elements_by_class_name('list-group-item')
    print(type(div_elements))
    print('div elements cnt = {}'.format(len(div_elements)))

    picture_index = 97
    for div_element in div_elements:
        img_path = div_element.get_attribute('href')
        if img_path.find('_100') != -1:
            print(img_path)
            print('正在下载第{}张图片'.format(picture_index))
            img_name = 'picture\\{}.jpg'.format(picture_index)
            img = requests.get(img_path,headers=headers).content
            with open(img_name, 'wb') as save_img:
                save_img.write(img)
            picture_index += 1

    time.sleep(sleep_time)
    driver.quit()  #关闭浏览器
    
download_picture("https://ss.netnr.com/wallpaper#26", "https://ss.netnr.com/wallpaper")
    

