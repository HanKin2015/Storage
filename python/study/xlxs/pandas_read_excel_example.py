# -*- coding: utf-8 -*-
"""
文 件 名: pandas_read_excel_example.py
文件描述: 使用pandas打开xlxs表格
作    者: HanKin
创建日期: 2023.09.05
修改日期：2023.09.05

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import pandas as pd

def match_vid_pid():
    """匹配usb设备
    """
    
    scanning_gun = '0525:A4A7'
    df = pd.read_excel('外设助手改进/外设助手改进专项.xlsx', sheet_name='兼容性列表')
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
            break

def main():
    """主函数
    """
    
    # 读取 Excel 文件
    df = pd.read_excel('外设助手改进/外设助手改进专项.xlsx', sheet_name='兼容性列表')

    # 打印数据框的前几行
    #print(df.head())
    
    # 打印工作表大小
    print(df.shape)
    
    # 遍历vid_pid列
    for index, vid_pid in enumerate(df['vid_pid']):
        vid_pids = vid_pid.split(';')
        is_valid = True
        for elem in vid_pids:
            if len(elem) != 9:
                is_valid = False
                break
        if not is_valid:
            print('index {} is invalid[{}]'.format(index+2, vid_pid))

    match_vid_pid()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
