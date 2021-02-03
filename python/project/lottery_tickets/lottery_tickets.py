# -*- coding: utf-8 -*-
"""
Created on 2021.01.30

@author: hankin
@desc:
    分析福利彩票双色球中奖号码
    网站：http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
@other:
    中国福利彩票双色球规则: 
    一等奖：当奖池资金低于1亿元时，奖金总额为当期高奖级奖金的75%与奖池中累积的资金之和，单注奖金按注均分，单注最高限额封顶500万元。当奖池资金高于1亿元（含）时，奖金总额包括两部分，一部分为当期高奖级奖金的55%与奖池中累积的资金之和，单注奖金按注均分，单注最高限额封顶500万元；另一部分为当期高奖级奖金的20%，单注奖金按注均分，单注最高限额封顶500万元。
    二等奖：奖金总额为当期高奖级奖金的25%，单注奖金按注均分，单注最高限额封顶500万元。
    三等奖：单注奖金固定为3000元。
    四等奖：单注奖金固定为200元。
    五等奖：单注奖金固定为10元。
    六等奖：单注奖金固定为5元。
    一等奖（6+1）中奖概率为：红球33选6乘以蓝球16选1=1/17721088=0.0000056%；
    二等奖（6+0）中奖概率为：红球33选6乘以蓝球16选0=15/17721088=0.0000846%；
    三等奖（5+1）中奖概率为：红球33选5乘以蓝球16选1=162/17721088=0.000914%；
    四等奖（5+0、4+1）中奖概率为：红球33选5乘以蓝球16选0=7695/17721088=0.0434%；
    五等奖（4+0、3+1）中奖概率为：红球33选4乘以蓝球16选0=137475/17721088=0.7758%；
    六等奖（2+1、1+1、0+1）中奖概率为：红球33选2乘以蓝球16选1=1043640/17721088=5.889%；
    共计中奖率：6.71%。
"""

import pandas as pd
import numpy as np
import requests
import bs4
import logging
from selenium import webdriver
import time
import datetime

def lottery_number_handler(lottery_number):
    '''彩票数字处理器
    
    @desc  将字符串类型的彩票数字转换为数字列表
    @param lottery_number: 字符串类型的彩票数字
    @return red_ball: 彩票数字红球列表
    @return blue_ball: 彩票数字蓝球列表
    '''
    
    #print(lottery_number)
    lottery_number = lottery_number.split(' ')
    #print(lottery_number)
    try:
        lottery_number.remove('')
    except:
        print('there are not space.')
        pass
    lottery_number = [lottery_number[i] for i in range(0,len(lottery_number)) if lottery_number[i] != '']
    #print(lottery_number)    
    lottery_number = [int(number) for number in lottery_number]
    
    # 红蓝球分离
    red_ball = lottery_number[:-1]
    blue_ball = lottery_number[-1:]
    return red_ball, blue_ball

def count_same_in_two_list(list1, list2):
    '''两个列表中相同元素个数
    
    @desc  两个列表中相同元素个数
    @param list1: 列表1
    @param list2: 列表2
    @return 相同元素个数
    '''

    same_list = [elem for elem in list1 if elem in list2]
    return len(same_list)

def is_win_a_prize_in_a_lottery(history_data, lottery_number):
    '''是否中奖
    
    @desc  是否在历史长河中中过哪些奖
    @param lottery_numbers: 7个数字的彩票号码
    @param history_data: 历史中奖数据
    @return prize_list: 中奖列表
    '''
    
    # 判断
    
    # 彩票号码处理
    red_ball, blue_ball = lottery_number_handler(lottery_number)
    
    prize_list = []
    
    prize_numbers = history_data['中奖号码'].values
    #print('prize_numbers len: {}.'.format(len(prize_numbers)))
    for prize_number in prize_numbers:
        #print('prize_numbers: {}.'.format(prize_number))
        red_prize_number, blue_prize_number = lottery_number_handler(prize_number)

        #print('red_prize_number: {}, blue_prize_number: {}.'.format(red_prize_number, blue_prize_number))
        
        count_same_red_ball = count_same_in_two_list(red_ball, red_prize_number)
        count_same_blue_ball = count_same_in_two_list(blue_ball, blue_prize_number)
        
        if count_same_blue_ball == 1:
            if count_same_red_ball <= 2:
                prize_list.append(6)
            elif count_same_red_ball == 3:
                prize_list.append(5)
            elif count_same_red_ball == 4:
                prize_list.append(4)
            elif count_same_red_ball == 5:
                prize_list.append(3)
            elif count_same_red_ball == 6:
                prize_list.append(1)
        else:
            if count_same_red_ball == 4:
                prize_list.append(5)
            elif count_same_red_ball == 5:
                prize_list.append(4)
            elif count_same_red_ball == 6:
                prize_list.append(2)
    
    print('sum: {}, prize_list: {}.'.format(len(prize_list), prize_list))

def get_history_data(is_online=True):
    '''获取历史中奖数据
    
    @desc  网站: http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
    @param is_online: 是否离线获取,分为网上在线爬取或者本地文件读取
    @return history_data: 返回历史中奖数据
    '''
    
    # 历史中奖数据文件保存
    save_data_file_path = './历史中奖数据.xlsx'
    # 历史中奖数据dataframe结构体
    history_data = pd.DataFrame()
    
    if is_online:
        # 历史中奖数据列名
        columns = []
        
        # 页面从1开始,但不包括50,20210203目前133页
        for page_index in range(1, 50):
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
            columns = np.delete(columns, len(columns)-1)
            
            if history_data.shape[0]:
                history_data = history_data.append(table_data)
            else:
                history_data = table_data.copy()
            print('DataFrame [history_data] shape: [{} x {}].'.format(history_data.shape[0], history_data.shape[1]))
        
        # 对历史中奖数据列名重命名
        print('history_data type: {}, columns: {}.'.format(type(history_data), columns))
        history_data.columns = columns
        
        # 保存文件到本地
        history_data.to_excel(save_data_file_path, index=False, header=True)
    else:
        history_data = pd.read_excel(save_data_file_path)
        
    return history_data

def get_weekday(date):
    '''统计分析历史中奖数据
    
    @desc  网站: http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
    @param is_online: 是否离线获取,分为网上在线爬取或者本地文件读取
    @return history_data: 返回历史中奖数据
    '''
    
    date = date.split('-')
    date = [int(elem) for elem in date]
    #date = np.array(date)
    #print(type(date), len(date), date)
    date = datetime.datetime.date(datetime.datetime(year=date[0], month=date[1], day=date[2]))
    #print(date.isoweekday())
    return date.isoweekday()
    
def statistics_analyse(history_data):
    '''统计分析历史中奖数据
    
    @desc  网站: http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
    @param is_online: 是否离线获取,分为网上在线爬取或者本地文件读取
    @return history_data: 返回历史中奖数据
    '''

    save_data_file_path = './统计分析历史中奖数据.xlsx'

    # 构造列名
    red_ball_number = list(range(1, 34))
    blue_ball_number = list(range(1, 17))
    columns = red_ball_number + blue_ball_number
    #print(columns)

    # 初始化值为0
    tuesday = np.zeros((49,), dtype=int, order='C')
    thursday = np.zeros((49,), dtype=int, order='C')
    sunday = np.zeros((49,), dtype=int, order='C')
    statistics = np.zeros((49,), dtype=int, order='C')
    statistics_dataframe = pd.DataFrame([tuesday, thursday, sunday, statistics], columns=columns)

    # 重命名索引值
    statistics_dataframe.index = ['tuesday', 'thursday', 'sunday', 'statistics']

    # 下标均以0开始,不包含列名和行名
    #statistics_dataframe.iloc[2, 0] = 123
    #statistics_dataframe.iloc[2, 33+15] = 123
    
    weekday_dict = {'2': 0, '4': 1, '7': 2}
    
    prize_numbers = history_data['中奖号码'].values
    for index, prize_number in enumerate(prize_numbers):
        #print(history_data['开奖日期'].loc[index])
        date = history_data['开奖日期'].loc[index]
        weekday = get_weekday(date)
        
        red_prize_number, blue_prize_number = lottery_number_handler(prize_number)
        for number in red_prize_number:
            statistics_dataframe.iloc[weekday_dict[str(weekday)], number-1] += 1
            statistics_dataframe.iloc[3, number-1] += 1
        for number in blue_prize_number:
            #print(number)
            statistics_dataframe.iloc[weekday_dict[str(weekday)], number+32] += 1
            statistics_dataframe.iloc[3, number+32] += 1
    
    # 保存结果到本地
    statistics_dataframe.to_excel(save_data_file_path, index=True, header=True)
    
if __name__ == '__main__':
    begin_time = time.time()
    
    # 获取历史中奖数据
    history_data = get_history_data(False)
    print('history_data.shape: {}.'.format(history_data.shape))
    
    # 彩票号码
    lottery_number = '01 06 14 32 22 26 07'
    
    # 查询是否中奖
    is_win_a_prize_in_a_lottery(history_data, lottery_number)
    
    # 统计分析历史中奖数据
    #statistics_analyse(history_data)
    
    end_time = time.time()
    print('共花费 {} s时间'.format(round(end_time - begin_time, 2)))



