# -*- coding: utf-8 -*-
"""
Created on 2021.01.30

@author: hankin
@desc:
    分析福利彩票双色球中奖号码
    网站：http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
"""

import pandas as pd
import  requests
import  bs4
import logging
from selenium import webdriver
import time




if __name__ == '__main__':
    begin_time = time.time()
    
    # 历史中奖数据文件保存
    save_data_file_path = './历史中奖数据.xlsx'
    # 历史中奖数据dataframe结构体
    data = pd.DataFrame()
    # 历史中奖数据列名
    columns = []
    
    # 页面从1开始,但不包括50
    for page_index in range(1, 4):
        # 爬取的网页地址
        url = 'http://kaijiang.zhcw.com/zhcw/html/ssq/list_{}.html'.format(page_index)
        
        # 使用read.html爬取表格数据
        table_data = pd.read_html(url, header=0, encoding='utf-8')[0]
        print('table count = {}, type = {}.'.format(len(table_data), type(table_data)))
        
        # 默认的header不如第0行,更换列名
        print(table_data.columns.values.tolist())
        print(table_data.iloc[0].values)
        columns = table_data.iloc[0].values
        
        # 去除0行和21行的数据,去除详细一列的数据
        table_data = table_data.drop([0,21])
        table_data = table_data.drop(['详细'],axis=1)
        
        if data.shape[0]:
            data = data.append(table_data)
        else:
            data = table_data.copy()
        print('DataFrame [data] shape: [{} x {}].'.format(data.shape[0], data.shape[1]))
    
    # 对历史中奖数据列名重命名
    data.rename(columns=columns, inplace=True)
    
    # 保存文件到本地
    data.to_excel(save_data_file_path, index=False, header=True)
        

    
    #get_estate_info(url, save_file_path)
    end_time = time.time()
    print('共花费 {} s时间'.format(round(end_time - begin_time, 2)))



