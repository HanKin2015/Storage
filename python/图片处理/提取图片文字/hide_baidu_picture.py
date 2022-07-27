# -*- coding: utf-8 -*-
"""
文 件 名: hide_baidu_picture.py
文件描述: 隐藏百度网页的百度图片
作    者: HanKin
创建日期: 2022.07.26
修改日期：2022.07.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

from selenium import webdriver
import time

driver = webdriver.Chrome()
driver.get("https://www.baidu.com/")

# 给搜索输入框标红的javascript脚本
js = "var q=document.getElementById(\"kw\");q.style.border=\"2px solid red\";"

# 调用给搜索输入框标红js脚本
driver.execute_script(js)

# 查看页面快照
driver.save_screenshot("redbaidu.png")

# js隐藏元素，将获取的图片元素隐藏
img = driver.find_element_by_xpath("//*[@id='lg']/img")
driver.execute_script('$(arguments[0]).fadeOut()', img)

# 向下滚动到页面底部
driver.execute_script("$('.scroll_top').click(function(){$('html,body').animate({scrollTop: '0px'}, 800);});")

# 查看页面快照
time.sleep(1)
driver.save_screenshot("nullbaidu.png")
time.sleep(3)

driver.quit()
