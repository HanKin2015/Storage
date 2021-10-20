# -*- coding: utf-8 -*-
"""
文 件 名: crawl_template.py
文件描述: 爬虫模板
备    注: 只需要修改g_urls和main函数
作    者: HanKin
创建日期: 2021.10.19
修改日期：2021.10.19

Copyright (c) 2021 HanKin. All rights reserved.
"""

import  requests
import  bs4

#网站
g_urls = [
            ["https://wwe.lanzoui.com/{}","div.d > div", 0]
         ]

#伪造浏览器访问
g_headers = {
                'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/94.0.4606.81 Safari/537.36',
            }

#超时参数
g_timeout = 2

def crawl(target):
    for url, regex, index in g_urls:
        target_url = url.format(target)
        html = ""
        try:
            html = requests.get(target_url, headers=g_headers, timeout=g_timeout)
        except Exception:
            print('wrong')
            return None
    
        soup = bs4.BeautifulSoup(html.text, "html.parser")
    
        content = soup.select(regex)
        if content and len(content) > index :
            return content[index].get_text().strip()
    return content

def main():
    content = crawl('iabrphqxs0j')
    print(content)

if __name__ == '__main__':
    main()











