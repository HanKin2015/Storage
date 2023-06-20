# -*- coding: utf-8 -*-
"""
文 件 名: analysis_upan_performance_data.py
文件描述: 分析upan_auto_copy.log文件
作    者: HanKin
创建日期: 2022.02.12
修改日期：2022.02.12

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import matplotlib.pyplot as plt

GENERATE_SPEED = []
READ_SPEED = []
WRITE_SPEED = []

def get_line(file_path):
    """
    当文件很大，而内存比较小的时候，可以考虑一行一行读取文件，或者分块读取文件。
    采用yield+next方式读取文件。
    """
    
    with open(file_path, 'r') as fd:
        for line_str in fd:
            yield line_str

def get_speed_data(line_str):
    """
    """
    
    pos_s = line_str.find('平均速度为')
    pos_e = line_str.find('MB/s')
    if pos_s != -1 and pos_e != -1:
        speed = float(line_str[pos_s+5:pos_e])
        #print(speed)
        
        global GENERATE_SPEED, READ_SPEED, WRITE_SPEED
        pos = line_str.find('生成数据')
        if pos != -1:
            GENERATE_SPEED.append(speed)
        pos = line_str.find('U盘拷贝到电脑')
        if pos != -1:
            READ_SPEED.append(speed)
        pos = line_str.find('电脑拷贝到U盘')
        if pos != -1:
            WRITE_SPEED.append(speed)

def line_chart():
    plt.rcParams['font.sans-serif'] = ['SimHei']
    
    #plt.plot(x_axis_data, y_axis_data, 'ro-', color='#4169E1', alpha=0.8, linewidth=1, label=label)
    plt.plot(range(len(GENERATE_SPEED)), GENERATE_SPEED, 'o-', alpha=0.8, linewidth=1, label='生成速度')
    plt.plot(range(len(READ_SPEED)), READ_SPEED, 'o-', alpha=0.8, linewidth=1, label='读速度')
    plt.plot(range(len(WRITE_SPEED)), WRITE_SPEED, 'o-', alpha=0.8, linewidth=1, label='写速度')
    
    plt.legend(loc="lower right")
    plt.xlabel('拷贝序号')
    plt.ylabel('速度(MB/s)')
    plt.show()

def main():
    """
    """
    
    file_path = 'upan_auto_copy.log'
    all_str = get_line(file_path)
    while True:
        try:
            line_str = next(all_str)
            #print(line_str.strip('\n'))
            get_speed_data(line_str)
        except StopIteration:
            print("Iteration is stopped.")
            break
    
    print(len(GENERATE_SPEED), len(READ_SPEED), len(WRITE_SPEED))
    print(GENERATE_SPEED)
    print(READ_SPEED)
    print(WRITE_SPEED)
    
    line_chart()

from decimal import Decimal,ROUND_HALF_UP
def smart_round(x, n):
    return str(Decimal(x).quantize(Decimal("0."+"0"*n), rounding=ROUND_HALF_UP))

def debug():
    data = 3.1415926
    print(round(data, 3))
    data = 3.1395926
    print(round(data, 3))
    print(smart_round(data, 3))
    print('{:.3f}'.format(round(data, 3)))
    print('{:.3f}'.format(data))

if __name__ == '__main__':
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
