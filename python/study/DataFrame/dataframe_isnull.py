# -*- coding: utf-8 -*-
"""
文 件 名: dataframe_isnull.py
文件描述: 判空
作    者: HanKin
创建日期: 2023.10.12
修改日期：2023.10.12

Copyright (c) 2023 HanKin. All rights reserved.
"""

import pandas as pd
import numpy as np

file_path = r'D:\Users\User\Desktop\外设\bug SN与ROM对应文档.xlsx'
data = pd.read_excel(file_path)

print(data.shape)

X86_serial_number_list = []
Android4_serial_number_list = []
Android8_serial_number_list = []
for index, os_version in enumerate(data['系统版本']):
    if os_version == 'Android4.2':
        Android4_serial_number_list.append(data.iloc[index]['SN码'])
    elif os_version == 'Android8.1':
        Android8_serial_number_list.append(data.iloc[index]['SN码'])
    elif not pd.isna(os_version):   # 使用None、''、np.nan都失败
        #print(os_version)
        X86_serial_number_list.append(data.iloc[index]['SN码'])
    elif not pd.isna(data.iloc[index]['SN码']):
        if data.iloc[index]['SN码'][0] == '7':
            print(index+2, data.iloc[index]['SN码'])

print(len(X86_serial_number_list), X86_serial_number_list)
print('')
print(len(Android4_serial_number_list), Android4_serial_number_list)
print('')
print(len(Android8_serial_number_list), Android8_serial_number_list)