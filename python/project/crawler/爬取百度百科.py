# -*- coding: utf-8 -*-
"""
Created on Wed Jul  1 13:58:50 2020

@author: Administrator
"""
import  requests
import  bs4



#网站
g_urls = [
    ["https://baike.baidu.com/item/{}","div.para", 0]
    ]

#伪造浏览器访问
g_headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
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
    return None

def main():
    content = crawl('2020年抗疫特别国债')
    print(content)
    
    content = crawl('禁忌搜索算法')
    print(content)

if __name__ == '__main__':
    main()







