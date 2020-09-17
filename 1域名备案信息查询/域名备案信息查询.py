# -*- coding: utf-8 -*-
"""
Created on Sat Jun 13 10:17:49 2020

@author: hejian-29996
@desc:
# 域名备案信息查询

输入一批域名，返回这批域名备案信息中的主办单位名称

比如，对于域名“www.sina.com”，返回“北京新浪互联信息服务有限公司”

可以通过第三方API来查询www.sina.com备案信息，如：
http://icp.chinaz.com/www.sina.com
https://www.beian88.com/sina.com
http://www.beianbeian.com/search/www.sina.com.html

第三方API可能不稳定，可能返回错误，可能返回输入验证码，你的代码需要尝试从多个第三方API获取信息来保证程序的输出。

其它要求：
1. 尽可能考虑过程中可能出现的异常
2. 合理地记录日志
3. 使用多线程来优化性能
4. 需单元测试
"""
 
import pandas as pd
import  requests
import  bs4
from concurrent.futures import ThreadPoolExecutor
import time
import logging
from concurrent_log_handler import ConcurrentRotatingFileHandler
import unittest

#第三方域名备案网站
g_domain_record_urls = [
        ["http://www.58icp.com/s/{}","table.table > tbody > tr > td", 3],
        ["http://icp.chinaz.com/{}", "div.pr.zI0 > ul > li > p > a", 0],
        ["http://www.beianbeian.com/search/{}.html", "tbody#table_tr > tr > td", 1]
        ]

#伪造浏览器访问
g_headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
        }

#超时参数
g_timeout = 2
#线程参数
g_thread_num = 10
#日志变量
global g_logger, g_handler, g_console
#全局变量,代理ip集合
g_proxies = []

"""
@desc   打开日志
"""
def open_log():
    global g_logger, g_handler, g_console
    g_logger = logging.getLogger(__name__)
    g_logger.setLevel(level = logging.INFO)
    #定义一个RotatingFileHandler，最多备份3个日志文件，每个日志文件最大5K
    g_handler = ConcurrentRotatingFileHandler("log.txt","a", maxBytes = 5*1024, backupCount=3)
    g_handler.setLevel(logging.INFO)
    formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    g_handler.setFormatter(formatter)
     
    g_console = logging.StreamHandler()
    g_console.setLevel(logging.INFO)
    g_console.setFormatter(formatter)
     
    g_logger.addHandler(g_handler)
    g_logger.addHandler(g_console)
    
"""
@desc   关闭日志
"""
def close_log():
    global g_logger, g_handler, g_console
    g_logger.removeHandler(g_handler)
    g_logger.removeHandler(g_console)

"""
@desc   获取代理IP
@param  无
@return 成功返回g_proxies,失败返回None
"""
def get_proxy_ip():
    g_logger.info('get proxy ip')
    proxy_url = "https://ip.jiangxianli.com/?page=1"
    try:
        html = requests.get(proxy_url, headers=g_headers, timeout=3)
    except Exception:
        g_logger.info('get proxy ip failed')
        return None
    soup = bs4.BeautifulSoup(html.text, "html.parser")
    
    #获取可用代理ip
    result = soup.select("div.layui-form > table > tbody > tr > td")
    #print(len(result))
    global g_proxies
    for i in range(0, len(result), 11):
        ip = result[i].get_text().strip()       #ip地址
        ep = result[i + 1].get_text().strip()   #端口
        proxy = ip + ':' + ep
        g_proxies.append(proxy) 
    g_logger.info('get proxy ip success')
    return g_proxies

"""
@desc  如果爬取失败则使用代理ip爬取
@param target_url:目标网址
@return 成功返回主办单位名称,失败返回None
"""
def get_by_proxy(target_url):
    g_logger.info('start get by proxy')
    global g_proxies
    for i in g_proxies:
        try:
            data = requests.get(target_url, headers=g_headers, proxies=g_proxies[i], timeout=g_timeout)
        except Exception:
            continue
            
        if data:
            return data
    g_logger.info('get by proxy failed')
    return None


"""
@desc   获取主办单位名称
@param  url:域名
@return 成功返回主办单位名称,失败返回None
"""
def get_organizer_name(url):
    for domain_record_url, regex, index in g_domain_record_urls:
        target_url = domain_record_url.format(url)
        html = ""
        try:
            html = requests.get(target_url, headers=g_headers, timeout=g_timeout)
        except Exception:
            if not html:
                html = get_by_proxy(target_url)
                if not html:
                    return 'domain is invalid'
    
        soup = bs4.BeautifulSoup(html.text, "html.parser")
    
        #获取主办单位名称
        organizer_name = soup.select(regex)
        if len(organizer_name) > index and organizer_name[index] :
            return organizer_name[index].get_text().strip()
    return 'domain is invalid'

"""
@desc   保存到本地
@parm   results:结果
@return 无
"""
def save_local(results):
    df = pd.DataFrame(results)
    df.rename(columns={0:'域名',1:'主办单位名称'},inplace=True)
    #print(df)
    df.to_csv('./results.csv', sep=',', index=False, encoding='gbk')
    g_logger.info('save result to local[./result.csv]')

"""
@desc   保存到本地
@parm   
@return 需要解析的域名
"""
def read_local():
    urls = []
    file_name = "./urls.txt"
    try:
        fp = open(file_name, "r")
        g_logger.info("{}域名文件打开成功".format(file_name))
        for line in fp.readlines():
            urls.append(line.strip())
        fp.close()
    except IOError:
        g_logger.error("文件打开失败, {}文件不存在".format(file_name))
    g_logger.info('读取域名文件成功')
    return urls

def main():      
    #获取代理ip,反爬虫
    get_proxy_ip()
    #print(g_proxies)
    
    #从文件读取需要解析的域名
    urls = read_local()
    #print(urls)
    
    #从三个域名备案网站获取主办单位名称
    results = []
    begin_time = time.time()
    tpe = ThreadPoolExecutor(max_workers=g_thread_num) # 创建一个最大容纳数量为10的线程池
    for index, url in enumerate(urls):
        g_logger.info("{}--当前域名为:{}".format(index+1, url))
        task = tpe.submit(get_organizer_name, url) # 通过submit提交执行的函数到线程池中       
        results.append([url, task.result()])
    tpe.shutdown()
    end_time = time.time()
    g_logger.info("共解析%d个域名,共花费%ss时间" % (len(urls), round(end_time - begin_time, 2)))
    
    #将结果保存到文件中
    save_local(results)

"""
@desc   单元测试
"""  
class unit_test(unittest.TestCase):
    def test_get_organizer_name(self):
        g_logger.info('start unit test')
        self.assertEqual('北京百度网讯科技有限公司', get_organizer_name('baidu.com'))
        self.assertEqual('domain is invalid', get_organizer_name('com.baidu'))
        self.assertNotEqual('新浪', get_organizer_name('sina.com'))
        self.assertNotEqual('domain is valid', get_organizer_name('com.sina'))
        g_logger.info('unit test done')
    
if __name__ == '__main__':
    #打开日志
    open_log()
    
    #单元测试
    unittest.main()
    
    #通过域名获取主办单位名称
    main()
    
    #关闭日志
    close_log()
