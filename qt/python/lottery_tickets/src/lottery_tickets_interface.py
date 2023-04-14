# -*- coding: utf-8 -*-
"""
文 件 名: lottery_tickets_interface.py
文件描述: 分析福利彩票双色球中奖号码
备    注: 网站：http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
作    者: HanKin
创建日期: 2021.01.30
修改日期：2023.02.21
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

Copyright (c) 2023 HanKin. All rights reserved.
"""

import pandas as pd
import numpy as np
import requests
import bs4
import logging
from selenium import webdriver
import time
import datetime
from log import logger
import os

# 单注奖金
PRIZE_MONEY = np.array([0, 5000000, 200000, 3000, 200, 10, 5, 0])

# 历史开奖数据存储的文件夹（因为文件名不固定）
HISTORY_PRIZE_DATA_PATH = './data/history_prize_data'

def lottery_number_handler(lottery_number):
    """彩票数字处理器
    
    @desc  将字符串类型的彩票数字转换为数字列表
    @param lottery_number: 字符串类型的彩票数字
    @return red_ball: 彩票数字红球列表
    @return blue_ball: 彩票数字蓝球列表
    """
    
    #logger.info(lottery_number)
    lottery_number = lottery_number.split(' ')
    #logger.info(lottery_number)
    try:
        lottery_number.remove('')
    except:
        logger.info('there are not space.')
        pass
    lottery_number = [lottery_number[i] for i in range(0,len(lottery_number)) if lottery_number[i] != '']
    #logger.info(lottery_number)    
    lottery_number = [int(number) for number in lottery_number]
    
    # 红蓝球分离
    red_ball = lottery_number[:-1]
    blue_ball = lottery_number[-1:]
    return red_ball, blue_ball

def count_same_in_two_list(list1, list2):
    """两个列表中相同元素个数
    
    @desc  两个列表中相同元素个数
    @param list1: 列表1
    @param list2: 列表2
    @return 相同元素个数
    """

    same_list = [elem for elem in list1 if elem in list2]
    return len(same_list)

def is_win_a_prize_in_a_lottery(history_data, lottery_number):
    """是否中奖
    
    @desc  是否在历史长河中中过哪些奖
    @param lottery_numbers: 7个数字的彩票号码
    @param history_data: 历史中奖数据
    @return prize_list: 中奖列表
    """
    
    # 判断
    logger.info('lottery_number: {}.'.format(lottery_number))
    
    # 彩票号码处理
    red_ball, blue_ball = lottery_number_handler(lottery_number)
    
    prize_list = []
    
    prize_numbers = history_data['中奖号码'].values
    #logger.info('prize_numbers len: {}.'.format(len(prize_numbers)))
    for prize_number in prize_numbers:
        #logger.info('prize_numbers: {}.'.format(prize_number))
        red_prize_number, blue_prize_number = lottery_number_handler(prize_number)

        #logger.info('red_prize_number: {}, blue_prize_number: {}.'.format(red_prize_number, blue_prize_number))
        
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
            else:
                prize_list.append(7)
    
    #logger.info('sum: {}, prize_list: {}.'.format(len(prize_list), sorted(prize_list)))
    total_cost = history_data.shape[0] * 2
    winning_prize_money = 0
    for prize_grade in prize_list:
        winning_prize_money += PRIZE_MONEY[prize_grade]
    logger.info('count grade 4: {}'.format(prize_list.count(4)))
    logger.info('count grade 5: {}'.format(prize_list.count(5)))
    logger.info('count grade 6: {}'.format(prize_list.count(6)))
    logger.info('max winning prize grade: {}'.format(min(prize_list) if len(prize_list) else 0))
    logger.info('winning prize ratio: {} / {}, {:.2f}%'.format(len(prize_list), history_data.shape[0], len(prize_list) / history_data.shape[0] * 100))
    logger.info('total_cost: {}'.format(total_cost))
    logger.info('winning_prize_money: {}\n'.format(winning_prize_money))
    return prize_list

def get_history_data(is_online=True, pages=50):
    """获取历史中奖数据
    
    @desc  网站: http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
    @param is_online: 是否离线获取,分为网上在线爬取或者本地文件读取
    @param pages: 页数
    @return history_data: 返回历史中奖数据
    """

    if not os.path.exists(HISTORY_PRIZE_DATA_PATH):
        os.makedirs(HISTORY_PRIZE_DATA_PATH)
    # 历史中奖数据dataframe结构体
    history_data = pd.DataFrame()
    
    if is_online:
        # 历史中奖数据列名
        columns = []
        
        # 页面从1开始,但不包括50,20210203目前133页
        for page_index in range(1, pages):
            # 爬取的网页地址
            url = 'http://kaijiang.zhcw.com/zhcw/html/ssq/list_{}.html'.format(page_index)
            
            # 使用read.html爬取表格数据
            table_data = pd.read_html(url, header=0, encoding='utf-8')[0]
            logger.info('table count = {}, type = {}.'.format(len(table_data), type(table_data)))
            
            # 默认的header不如第0行,更换列名
            logger.info(table_data.columns.values.tolist())
            logger.info(table_data.iloc[0].values)
            columns = table_data.iloc[0].values
            
            # 去除0行和21行的数据,去除详细一列的数据
            table_data = table_data.drop([0,21])
            table_data = table_data.drop(['详细'],axis=1)
            columns = np.delete(columns, len(columns)-1)
            
            if history_data.shape[0]:
                history_data = history_data.append(table_data)
            else:
                history_data = table_data.copy()
            logger.info('DataFrame [history_data] shape: [{} x {}].'.format(history_data.shape[0], history_data.shape[1]))
        
        # 对历史中奖数据列名重命名
        logger.info('history_data type: {}, columns: {}.'.format(type(history_data), columns))
        history_data.columns = columns
        
        issue_number_list = list(history_data['期号'])
        issue_number_list = list(map(int, issue_number_list))
        start_issue_number = min(issue_number_list)
        end_issue_number = max(issue_number_list)
        for old_file in os.listdir(HISTORY_PRIZE_DATA_PATH):
            old_file_path = '{}/{}'.format(HISTORY_PRIZE_DATA_PATH, old_file)
            os.remove(old_file_path)
        # 历史开奖数据文件保存
        history_prize_data_file_path = '{}/{}-{}.xlsx'.format(HISTORY_PRIZE_DATA_PATH, start_issue_number, end_issue_number)
        # 保存文件到本地
        history_data.to_excel(history_prize_data_file_path, index=False, header=True)
    else:
        history_prize_data_file_path = os.listdir(HISTORY_PRIZE_DATA_PATH)
        if len(history_prize_data_file_path) != 1:
            logger.error('history prize data file path is null')
        else:
            history_prize_data_file_path = '{}/{}'.format(HISTORY_PRIZE_DATA_PATH, history_prize_data_file_path[0])
            history_data = pd.read_excel(history_prize_data_file_path)
        
    return history_data

def get_weekday(date):
    """统计分析历史中奖数据
    
    @desc  网站: http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
    @param is_online: 是否离线获取,分为网上在线爬取或者本地文件读取
    @return history_data: 返回历史中奖数据
    """
    
    date = date.split('-')
    date = [int(elem) for elem in date]
    #date = np.array(date)
    #logger.info(type(date), len(date), date)
    date = datetime.datetime.date(datetime.datetime(year=date[0], month=date[1], day=date[2]))
    #logger.info(date.isoweekday())
    return date.isoweekday()
    
def statistics_analyse(history_data):
    """统计分析历史中奖数据
    
    @desc  网站: http://kaijiang.zhcw.com/zhcw/html/ssq/list_1.html
    @param is_online: 是否离线获取,分为网上在线爬取或者本地文件读取
    @return history_data: 返回历史中奖数据
    """

    save_data_file_path = './统计分析历史中奖数据.xlsx'

    # 构造列名
    red_ball_number = list(range(1, 34))
    blue_ball_number = list(range(1, 17))
    columns = red_ball_number + blue_ball_number
    #logger.info(columns)

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
        #通过期号来控制数据范围采集
        date_number = history_data['期号'].loc[index]
        #选择2020年至今[2020001,]
        if int(date_number) < 2020001:
            continue
        
        #logger.info(history_data['开奖日期'].loc[index])
        date = history_data['开奖日期'].loc[index]
        weekday = get_weekday(date)
        
        red_prize_number, blue_prize_number = lottery_number_handler(prize_number)
        for number in red_prize_number:
            statistics_dataframe.iloc[weekday_dict[str(weekday)], number-1] += 1
            statistics_dataframe.iloc[3, number-1] += 1
        for number in blue_prize_number:
            #logger.info(number)
            statistics_dataframe.iloc[weekday_dict[str(weekday)], number+32] += 1
            statistics_dataframe.iloc[3, number+32] += 1
    
    # 保存结果到本地
    statistics_dataframe.to_excel(save_data_file_path, index=True, header=True)
    return statistics_dataframe

def generate_lottery_number(statistics_data=None):
    save_data_file_path = './统计分析历史中奖数据.xlsx'
    statistics_data = pd.read_excel(save_data_file_path, index=False)
    logger.info(statistics_data.shape)
    #logger.info(statistics_data)
    
    red_ball_number = list(range(1, 34))
    blue_ball_number = list(range(1, 17))
    red_ball_count =  statistics_data.iloc[2].values[1:34]
    blue_ball_count  = statistics_data.iloc[2].values[34:50]
    
    red_ball_count, red_ball_number = zip(*sorted(zip(red_ball_count, red_ball_number), reverse=True))
    logger.info(red_ball_number)
    logger.info(red_ball_count)
    
    blue_ball_count, blue_ball_number = zip(*sorted(zip(blue_ball_count, blue_ball_number), reverse=True))
    logger.info(blue_ball_number)
    logger.info(blue_ball_count)
    
    lottery_number1 = [sorted(red_ball_number[0:6]), blue_ball_number[0:1]]
    lottery_number2 = [sorted(red_ball_number[33-6:]), blue_ball_number[-1:]]
    logger.info('频繁率高推荐彩票号码:', lottery_number1)
    logger.info('频繁率低推荐彩票号码:', lottery_number2)

def debug():
    issue_number_list = ['2023019', '2023018', '2023017', '2023016', '2023015', '2023014', '2023013', '2023012', '2023011', '2023010', '2023009', '2023008', '2023007', '2023006', '2023005', '2023004', '2023003', '2023002', '2023001', '2022150']
    issue_number_list = list(map(int, issue_number_list))
    print(issue_number_list)
    minn = min(issue_number_list)
    maxx = max(issue_number_list)
    print(minn, maxx)

def main():
    """主函数
    """
    
    # 获取历史开奖数据
    history_data = get_history_data(False, 50)
    logger.info('history_data.shape: {}.'.format(history_data.shape))

    # 彩票号码
    lottery_numbers = ['3 10 13 17 26 33 8', '1 2 4 9 12 16 12', '22 14 6 27 20 18 12', '01 06 14 20 22 26 07']
    
    # 查询是否中奖
    for lottery_number in lottery_numbers:
        is_win_a_prize_in_a_lottery(history_data, lottery_number)
    
    # 统计分析历史中奖数据
    #statistics_analyse(history_data)
    
    # 生成一个彩票号码
    generate_lottery_number()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))
