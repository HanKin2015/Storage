# -*- coding: utf-8 -*-
"""
文 件 名: scroll_opt.py
文件描述: 模拟滚动条滚动到底部

1、什么是document.body？

返回html dom中的body节点 即<body>
2、什么是document.documentElement？

返回html dom中的root 节点 即<html>
总结一下：

这个涉及到浏览器机制，chrome、firefox和ie之前有区别；

1）如果页面中存在DTD，那么就可以使用document.documentElement来获取某些值；

2）如果不存在DTD，就不能通过document.documentElement来获取了，就通过document.body来获取某些值了

可以兼容解决方案：
var scrollTop = document.documentElement.scrollTop || document.body.scrollTop;

作    者: HanKin
创建日期: 2022.07.26
修改日期：2022.07.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

from selenium import webdriver
import time

driver = webdriver.Chrome()

# 这个底部去不了，因为是动态加载，只会到达当时的底部
#driver.get("https://movie.douban.com/typerank?type_name=剧情&type=11&interval_id=100:90&action=")

driver.get("https://movie.douban.com/subject/1291828/")

# 向下滚动10000像素
#js = "document.body.scrollTop=10000"
js = "document.documentElement.scrollTop=10000"
#js="var q=document.documentElement.scrollTop=10000"
time.sleep(3)

#查看页面快照
driver.save_screenshot("douban.png")

# 执行JS语句
driver.execute_script(js)
time.sleep(3)

#查看页面快照
driver.save_screenshot("newdouban.png")

driver.quit()

