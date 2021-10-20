# -*- coding: utf-8 -*-
"""
文 件 名: get_lzy_download_url.py
文件描述: 获取蓝奏云下载直连链接(https://www.jianshu.com/p/079662967b38)
备    注: 有点点复杂，但是可以用来学习爬虫
作    者: HanKin
创建日期: 2021.10.19
修改日期：2021.10.19

Copyright (c) 2021 HanKin. All rights reserved.
"""

from bs4 import BeautifulSoup
import requests
import re
import time
import json

def GetHeaders(url):
    headers = {
        'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.81 Safari/537.36',
        'referer': url,     #蓝奏云分享文件链接地址
        'Accept-Language': 'zh-CN,zh;q=0.9',
    }
    return headers

def GetRealAddress(url):
    # 获取分享页面html文件
    res = session.get(url, headers=GetHeaders(url))
    # 引入BeautifulSoup库对html进行处理，获取iframe中的出现的js文件
    soup = BeautifulSoup(res.text, 'html.parser')
    url2 = 'https://www.lanzoui.com' + soup.find('iframe')['src']
    print(url2)
    res2 = session.get(url2, headers=GetHeaders(url2))

    # 正则提取请求三个参数(没有获取到ajaxdata？？？)
    ajaxdata = re.findall(r'var ajaxdata = \'([\w]+?)\';', res2.text)
    params = re.findall(r'var [\w]{8} = \'([\w]+?)\';', res2.text)
    print(ajaxdata)
    print(params)

    # 请求下载地址
    url3 = 'https://www.lanzoui.com/ajaxm.php'
    data = {
        'action':'downprocess',
        'sign':params[0],
        'ves':1,
    }
    res3 = session.post(url3, headers=GetHeaders(url2), data=data)
    res3 = json.loads(res3.content)
    print(res3)

    # 请求最终重定向地址
    try:
        url4 = res3['dom']+'/file/'+res3['url']
    except:
        while True:
            res3 = session.post(url3,headers=GetHeaders(url2),data=data)
            res3 = json.loads(res3.content)
            a = res3.get("inf")
            #print(res3)
            if a == "已超时，请刷新":
                print("正在为您尝试第二次爬取，请稍后...")
            else:
                break
    else:
        pass
    print(url4)
    headers2 = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.81 Safari/537.36',
        'Accept-Language': 'zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2',
    }
    res4 = session.head(url4, headers=headers2)
    file_address = res4.headers['Location']

    return file_address

if __name__ == '__main__':
    session = requests.session()
    address = GetRealAddress("https://wwe.lanzoui.com/iabrphqxs0j")
    r = requests.get(address) 
    
    # 将下载的文件写入本地
    with open("暴力删除文件.bat",'wb') as f:
        f.write(r.content)