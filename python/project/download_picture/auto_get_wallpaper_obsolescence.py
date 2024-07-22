# -*- coding: utf-8 -*-
"""
文 件 名: auto_get_wallpaper_obsolescence.py
文件描述: 爬虫方式下载桌面壁纸（使用chrome驱动方式在这个网站已行不通）
作    者: HanKin
创建日期: 2024.07.22
修改日期：2024.07.22

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
from selenium import webdriver
import requests
from PIL import Image
from io import BytesIO
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
 
# 图片网页规则
url_regex = [
        ["https://ss.netnr.com/wallpaper", "a.list-group-item", 1]
        ]

#伪造浏览器访问
headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
        }

# 睡眠等待时间
sleep_time = 2
 
def download_picture(url, save_file_path):
    """下载图片
    :param url: 图片网页地址
    :param save_file_path: 保存目录路径
    :return null
    """
    
    # 浏览器驱动
    options = webdriver.ChromeOptions()
    service = Service(executable_path=r"C:\Program Files\Google\Chrome\Application\chromedriver.exe")
    driver = webdriver.Chrome(service=service, options=options)    # 打开浏览器
    driver.maximize_window() # 最大化窗口
    #driver.set_window_size(1000,30000) # 这种方式抓取需要拉动滑滚条的页面内容不可取
    
    driver.get(url) # 打开网页
    time.sleep(sleep_time)   # 时刻需要睡眠等待一下

    # 滚动网页解锁更多的图片
    #driver.execute_script("window.scrollBy(0,30000)")
    #time.sleep(sleep_time*10)

    div_elements = driver.find_element(By.CLASS_NAME, "container-fluid p-lg-5 py-4")
    print(type(div_elements))
    print('div elements cnt = {}'.format(len(div_elements)))

    picture_index = 97
    for div_element in div_elements:
        img_path = div_element.get_attribute('href')
        if img_path.find('_100') != -1:
            print(img_path)
            print('正在下载第{}张图片'.format(picture_index))
            img_name = 'picture\\{}.jpg'.format(picture_index)
            
            # 使用requests获取图片内容
            response = requests.get(img_path, headers=headers).content
            
            # 检查请求是否成功
            if response.status_code == 200:
                # 将图片内容转换为文件流
                img_file = BytesIO(response.content)
                # 使用Pillow打开图片
                img = Image.open(img_file)
                
                # 显示图片
                img.show()
                break
                
                with open(img_name, 'wb') as save_img:
                    save_img.write(img)
            else:
                print("无法获取图片")
            picture_index += 1

    time.sleep(sleep_time)
    driver.quit()  #关闭浏览器
    return
    
download_picture("https://ss.netnr.com/wallpaper#26", "https://ss.netnr.com/wallpaper")
    

