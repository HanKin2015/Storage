# -*- coding: utf-8 -*-
"""
Created on Wed Sep  9 15:41:16 2020

@author: Administrator
"""

import pandas as pd
import numpy as np

def analysis_house_sold(data):
    '''
    输入dataframe数据
    返回dataframe数据
    '''
    sold_list, unsold_list, rate_list = [], [], []

    unsold_data = data[data.销售状态 == '可售']
    areas = np.sort(unsold_data.建筑面积.unique())
    print(areas)

    sold_cnt = data.shape[0]
    unsold_cnt = unsold_data.shape[0]
    rate = (sold_cnt - unsold_cnt) / sold_cnt
    rate = format(rate, '.2%')
    sold_list.append(sold_cnt)
    unsold_list.append(unsold_cnt)
    rate_list.append(rate)

    #计算出售情况
    for area in areas:
        sold_cnt = data[data.建筑面积 == area].shape[0]
        unsold_cnt = unsold_data[unsold_data.建筑面积 == area].shape[0]
        rate = (sold_cnt - unsold_cnt) / sold_cnt
        rate = format(rate, '.2%')

        sold_list.append(sold_cnt)
        unsold_list.append(unsold_cnt)
        rate_list.append(rate)
    return sold_list, unsold_list, rate_list

def read_data():
    analysis_result = pd.DataFrame(columns=['对应栋号', '出售状态', '总共数量', '100平方', '124平方', '142平方'])

    data = pd.read_excel('./依云曦府.xlsx', index=False, sheet_name=None)
    sheet_names = list(data.keys())
    print(sheet_names)
    for sheet_name in sheet_names:
        data = pd.read_excel('./依云曦府.xlsx', index=False, sheet_name=sheet_name)
        sold_list, unsold_list, rate_list = analysis_house_sold(data)
        print("sold_list size = ", len(sold_list), "unsold_list size = ", len(unsold_list))
        for i in range(4 - len(sold_list)):
            sold_list.append(0)
            unsold_list.append(0)
            rate_list.append(0)
        
        sold_list.insert(0, '全部')
        sold_list.insert(0, sheet_name)
        unsold_list.insert(0, '未售')
        unsold_list.insert(0, sheet_name)
        rate_list.insert(0, '去化率')
        rate_list.insert(0, sheet_name)
        nan_list = [np.NaN, np.NaN, np.NaN, np.NaN, np.NaN, np.NaN]
        
        df = pd.DataFrame([sold_list, unsold_list, rate_list, nan_list], columns=analysis_result.columns)
        analysis_result = analysis_result.append(df, ignore_index=True)
        
        #print(analysis_result)
    return analysis_result

if __name__ == '__main__':
    analysis_result = read_data()
    print(analysis_result)
    analysis_result.to_excel('./依云曦府销售情况.xlsx', index=False)








