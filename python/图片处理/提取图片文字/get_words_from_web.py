# -*- coding: utf-8 -*-
"""
文 件 名: get_words_frome_web.py
文件描述: 目前无法打开，需要验证码验证
作    者: HanKin
创建日期: 2022.07.26
修改日期：2022.07.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
from urllib.request import urlretrieve
import subprocess
from selenium import webdriver

# 创建新的selenium driver
driver = webdriver.Chrome()

# 调用浏览器
driver.get('http://www.amazon.com/War-Peace-Leo-Nikolayevich-Tolstoy/dp/1427030200')

# 点击图片
driver.find_element_by_xpath("//div[@id='img-canvas']/img").click()
time.sleep(5)
#
imageList = set()
# 等箭头可以点击时，开始翻页
while "pointer" in driver.find_element_by_id("sitbReaderRightPageTurner").get_attribute('style'):
    driver.find_element_by_id("sitbReaderRightPageTurner").click()
    time.sleep(2)
    # 获取已经加载的新页面（一次可加载多个，但是重复的页面不能进到集合里）
    pages = driver.find_elements_by_xpath("//div[@class='pageImage']/div/img")
    for page in pages:
        image = page.get_attribute("src")
        imageList.add(image)
        # print(imageList)
driver.quit()

# 用Tesseract处理我们收集的图片URL链接
for image in sorted(imageList):
    # 保存图片
    urlretrieve(image, "page.jpg")
    p = subprocess.Popen(["tesseract", "page.jpg", "page"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    f = open("page.txt", 'r')
    p.wait()
    print(f.read())

