# -*- coding: utf-8 -*-
"""
Created on Fri Sep 18 13:38:46 2020

@author: hankin
@desc:
    爬取长沙房地产开发商房屋销售情况
    网站：http://www.cszjxx.net/floorinfo/202004160830
    先以越秀亲爱里为例
"""

import pandas as pd
import  requests
import  bs4
import logging

#日志文件
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='./crawler.log',
                    filemode='a')

#房地产楼盘链接id
estate_ids = [202004160830, 202005070287, 202006230442]

#链接正则
url_regex = [
        ["http://www.cszjxx.net/floorinfo/{}","table.table > tbody > tr > td", 3]
        ]

#伪造浏览器访问
headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
        }

#爬取数据超时参数
timeout = 2

def write_file(content, file_path):
    '''
    '''
    
    logging.info('正在写入{}'.format(file_path))
    try:
        with open(file_path, 'w', encoding='utf-8') as f:
            for elem in content:
                f.write(elem+'\n')
    except Exception as ex:
        logging.error('打开文件失败, error={}'.format(ex))

def read_file(file_path):
    '''
    '''
    
    logging.info('正在读取{}'.format(file_path))
    content_list = []
    
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content_list = f.readlines() 
    except Exception as ex:
        logging.error('打开文件失败, error={}'.format(ex))
    
    return content_list
    
def get_proxy_ip():
    """获取代理IP
    """
    
    proxy_url = "https://ip.jiangxianli.com/?page=1"
    try:
        html = requests.get(proxy_url, headers=headers, timeout=timeout)
    except Exception:
        logging.error('get proxy html content msg failed')
        return None
    
    soup = bs4.BeautifulSoup(html.text, "html.parser")
    
    #获取可用代理ip
    result = soup.select("div.layui-form > table > tbody > tr > td")
    
    proxies = []
    for i in range(0, len(result), 11):
        ip = result[i].get_text().strip()       #ip地址
        ep = result[i + 1].get_text().strip()   #端口
        proxy = ip + ':' + ep
        proxies.append(proxy)  
    
    write_file(proxies, './proxies.txt')

def crawler_by_proxy(target_url):
    """通过代理爬虫
    @desc  如果爬取失败则使用代理ip爬取
    @param target_url:目标网址
    @return 成功返回主办单位名称,失败返回None
    """
    
    proxies = read_file('./proxies.txt')
    logging.info('there are {} useful proxy ip'.format(len(proxies)))
    for proxy in proxies:
        try:
            html = requests.get(target_url, headers=headers, proxies=proxy, timeout=timeout)
        except Exception:
            logging.warn('{} is invalid'.format(proxy))
            continue
            
        if html:
            return html
    return None

def crawler():
    for url, regex, index in url_regex:
        print(url)
    get_proxy_ip()

if __name__ == '__main__':
    crawler()

