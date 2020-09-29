# -*- coding: utf-8 -*-
"""
Created on Fri Sep 18 13:38:46 2020

@author: hankin
@desc:
    爬取长沙房地产开发商房屋销售情况
    网站：http://www.cszjxx.net/floorinfo/202006230442
    先以梅溪湖依云曦城楼盘为例
"""

import pandas as pd
import  requests
import  bs4
import logging
from selenium import webdriver
import time

#日志文件
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[%(funcName)s line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='./crawler.log',
                    filemode='a')

#房地产楼盘链接id
estate_ids = [202004160830, 202005070287, 202006230442]

#链接正则
url_regex = [
        ["http://www.cszjxx.net/floorinfo/{}","div.hs_xqxx > table > tbody > tr > td", 3],
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

def get_estate_info(url, save_file_path):
    '''获取楼盘信息
    '''
    chromedriver_path = r"C:/Program Files (x86)/Google/Chrome/Application/chromedriver.exe"
    driver = webdriver.Chrome(chromedriver_path)    #打开浏览器
    driver.maximize_window() #最大化窗口
    
    driver.get(url) #打开网页
    time.sleep(2)   #时刻需要睡眠等待一下
    
    div_elements = driver.find_elements_by_class_name('hs_zk')
    print(type(div_elements))
    print('div elements cnt = {}'.format(len(div_elements)))
    
    sheet_names = ['项目简介', '楼栋信息']
    #建立sheet_names
    table = pd.read_html(driver.page_source)[1]
    hourse_info = pd.DataFrame(table)
    hourse_numbers = hourse_info['对应栋号'].values
    print(hourse_numbers)
    sheet_names.extend(hourse_numbers.tolist())
    print(sheet_names)
    
    #print(driver.find_element_by_partial_link_text('点击加载更多'))
    #print(driver.find_element_by_link_text('点击加载更多'))
    #print(driver.find_element_by_name('点击加载更多'))
    #elements = driver.find_elements_by_xpath(".//*[@class='hs_table2']")
    #print(len(elements))
    #for div_idx in range(1, len(elements)+1, 1):
    
    div_ids = []
    for element in driver.find_elements_by_xpath(".//*[@class='hs_table2']"):
        #print(element.get_attribute('id'))
        div_ids.append(element.get_attribute('id'))
    
    #for div_idx, div_element in enumerate(div_elements, start=1):
    for div_element, div_id in zip(div_elements, div_ids):
        print('open div(id = {}) 展开户室列表'.format(div_id))
        time.sleep(3)
        driver.execute_script('arguments[0].click();', div_element)
        tbody_idx = 1
        
        while True:
            time.sleep(5)
            tr_element = driver.find_elements_by_xpath(".//*[@id='{}']/table/tbody[{}]/tr".format(div_id, tbody_idx))
            #print(len(tr_element))
            tr_idx = len(tr_element)
            if tr_idx == 0:
                print('已经到底了')
                break
            try:
                td_element = driver.find_element_by_xpath(".//*[@id='{}']/table/tbody[{}]/tr[{}]/td[1]".format(div_id, tbody_idx, tr_idx))
                print('open tr(index = {}) 点击加载更多'.format(tr_idx))
                driver.execute_script('arguments[0].click();', td_element)
                tbody_idx = tbody_idx + 1
            except Exception as ex:
                print(ex)
                break
            
    time.sleep(2)
    print('open all done')
    
    html = driver.page_source
    tables = pd.read_html(html) #返回一个List,里面封装的是Dataframe
    time.sleep(2)
    print('table count = {}'.format(len(tables)))
    writer = pd.ExcelWriter(save_file_path)
    for sheet_name, table in zip(sheet_names, tables):
        pd.DataFrame(table).to_excel(writer, index=False, sheet_name=sheet_name)
    writer.save()
    writer.close()
    time.sleep(2)
    driver.quit()  #关闭浏览器

def get_html_table_data():
    data = pd.read_html('http://www.cszjxx.net/floorinfo/202004160830')[2]
    #data.to_csv('./result.csv', index=False)
    print(data)

def crawler():
    for url, regex, index in url_regex:
        print(url)
    get_proxy_ip()

if __name__ == '__main__':
    #crawler()
    begin_time = time.time()
    url = 'http://www.cszjxx.net/floorinfo/202006230442'
    save_file_path = './梅溪湖依云曦城楼盘.xlsx'
    get_estate_info(url, save_file_path)
    end_time = time.time()
    print('共花费 {} s时间'.format(round(end_time - begin_time, 2)))
    #get_html_table_data()

