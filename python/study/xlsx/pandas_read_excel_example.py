# -*- coding: utf-8 -*-
"""
文 件 名: pandas_read_excel_example.py
文件描述: 使用pandas打开xlsx表格
作    者: HanKin
创建日期: 2023.09.05
修改日期：2024.01.25

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import pandas as pd

XLSX_FILE_PATH = r"D:\Demo\additional_data\device_helper\compatibility_list.xlsx"

def match_vid_pid():
    """匹配usb设备
    """
    
    scanning_gun = '0525:A4A7'
    df = pd.read_excel(XLSX_FILE_PATH, sheet_name='Sheet1')
    found_count = 0
    for index, vid_pid in enumerate(df['vid_pid']):
        vid_pids = vid_pid.split(';')
        is_found = False
        for elem in vid_pids:
            if scanning_gun.lower() == elem.lower():
                is_found = True
                break
        if is_found:
            print('usb device [{}] is found in index {}[{}]'.format(scanning_gun, index+2, vid_pid))
            print('{}'.format(df.iloc[index]['remark']))
            found_count += 1
    if found_count == 0:
        print('usb device [{}] is not found'.format(scanning_gun))

def check_vid_pid_valid():
    """检查vid_pid列合法性
    """
    # 读取 Excel 文件
    df = pd.read_excel(XLSX_FILE_PATH, sheet_name='Sheet1')

    # 打印数据框的前几行
    #print(df.head())
    
    # 打印工作表大小
    print(df.shape)
    
    # 遍历vid_pid列
    invalid_count = 0
    for index, vid_pid in enumerate(df['vid_pid']):
        vid_pids = vid_pid.split(';')
        is_valid = True
        for elem in vid_pids:
            if len(elem) != 9:
                is_valid = False
                break
        if not is_valid:
            print('index {} is invalid[{}]'.format(index+2, vid_pid))
            invalid_count += 1
    print('invalid_count = {}'.format(invalid_count))

def unrepeat():
    df = pd.read_excel(XLSX_FILE_PATH, sheet_name='Sheet1')
    zip_list = list(zip(df['model'], df['vendor'], df['vid_pid']))
    duplicate = []
    for item in zip_list:
        if zip_list.count(item) > 1 and item not in duplicate:
            duplicate.append(item)
    print('there are {} duplicates'.format(duplicate))

def main():
    """主函数
    """
    
    check_vid_pid_valid()
    unrepeat()
    match_vid_pid()
    
    x = [1, 2, 3, 4]
    y = [11, 22, 33, 44]
    z = zip(x, y)
    print(z)
    for item in z:
        print(item)
    print(type(z))

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
