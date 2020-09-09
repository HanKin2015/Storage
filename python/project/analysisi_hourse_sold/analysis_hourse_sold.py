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
	cnt, unsold_cnt = [], []
    
	unsold_data = data[data.销售状态 == '可售']
	areas = np.sort(unsold_data.建筑面积.unique())
	#print(areas)
    
	cnt.append(data.shape[0])
	unsold_cnt.append(unsold_data.shape[0])
    
    #计算出售情况
	for area in areas:
		cnt.append(data[data.建筑面积 == area].shape[0])
		unsold_cnt.append(unsold_data[unsold_data.建筑面积 == area].shape[0])
	return cnt, unsold_cnt

def read_data():
	analysis_result = pd.DataFrame(columns=['对应栋号', '出售状态', '总共数量', '100平方', '124平方', '142平方'])
	
	data = pd.read_excel('./依云曦府.xlsx', index=False, sheet_name=None)
	sheet_names = list(data.keys())
	print(sheet_names)
	for sheet_name in sheet_names:
		data = pd.read_excel('./依云曦府.xlsx', index=False, sheet_name=sheet_name)
		cnt, unsold_cnt = analysis_house_sold(data)
		cnt.insert(0, '全部')
		cnt.insert(0, sheet_name)
		unsold_cnt.insert(0, '未售')
		unsold_cnt.insert(0, sheet_name)
		
		df = pd.DataFrame([cnt, unsold_cnt], columns=analysis_result.columns)
		analysis_result = analysis_result.append(df, ignore_index=True)
		
		#print(analysis_result)
	return analysis_result

if __name__ == '__main__':
	analysis_result = read_data()
	print(analysis_result)
	analysis_result.to_excel('./依云曦府销售情况.xlsx', index=False)
	
	
	
	
	
	
	
	
	
	