# -*- coding: utf-8 -*-
"""
Created on Mon May 18 09:07:44 2020

@author: Administrator
"""

import requests
from lxml import etree
 
#必应图片网页地址
url = 'https://bing.ioliu.cn/'
#浏览器参数
header = {
    'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.132 Safari/537.36',
    'Referer':'http://bing.ioliu.cn'
}
#图片的张数
number = 0
 
html = requests.get(url,headers=header).text    #下载网页
etree_html = etree.HTML(html)                   #构造xpath的解析对象
img_url = etree_html.xpath('//img/@src')        #获取图片地址
#print(img_url)
for img_list in img_url:                        #下载图片并保存至指定位置
    img = requests.get(img_list,headers=header).content
    number+=1
    print('正在下载第{}张图片'.format(number))
    img_name = 'picture\\{}.jpg'.format(number)
    with open(img_name,'wb') as save_img:
        save_img.write(img)
 