# -*- coding: utf-8 -*-
"""
文 件 名: calc_time_interval.py
文件描述: 计算wireshark数据包之间的时间间隔
作    者: HanKin
备    注: 
创建日期: 2025.01.20
修改日期：2025.01.20

Copyright (c) 2025 HanKin. All rights reserved.
"""
import pandas as pd

# 读取导出的 CSV 文件
df = pd.read_csv('vm6.csv')

# 假设时间戳在 'Time' 列中，转换为 datetime 格式
#df['Time'] = pd.to_datetime(df['Time'])

# 计算时间差
#df['Time_Diff'] = df['Time'].diff().dt.total_seconds()

# 确保 Time 列是浮点数类型
df['Time'] = df['Time'].astype(float)
# 计算时间差
df['Time_Diff'] = df['Time'].diff()

# 找到时间差大于 1 秒的行
result = df[df['Time_Diff'] > 0.7]

print(result)
