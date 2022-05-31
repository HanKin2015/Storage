# -*- coding: utf-8 -*-
"""
文 件 名: log.py
文件描述: 学习logging库
作    者: HanKin
创建日期: 2022.05.30
修改日期：2022.05.30
Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import logging
import pandas as pd

# 数据路径
data_size = 1024    # 单位MB，即1GB大小文件

# U盘盘符
upan_path = 'E'

# 是否为Windows系统
is_windows = False
if sys.platform == 'win32' or sys.platform == 'win64':
    is_windows = True
    
# 创建结果备份文件夹
if not os.path.exists('./backup/'):
    os.makedirs('./backup/')

# 创建日志文件夹
if not os.path.exists('./log/'):
    os.makedirs('./log/')
# 配置日志
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S',
                    filename='./log/process.log',
                    filemode='a')
# 开启debug日志方法（创建一个debug文件即可）
if os.path.exists('debug'):
    logging.getLogger().setLevel(logging.DEBUG)

def main():
    data = {'Name': ['xiaoming', 'zhangsan', 'lisi'], 'Age':[10, 11, 21]}
    df = pd.DataFrame(data)
    logging.info('{}'.format(df))
    logging.error('{}'.format(df))
    logging.warning('{}'.format(df))
    
    score = 87.45
    now_time = datetime.datetime.now().strftime('%m-%d-%H-%M')
    df.to_csv('./result.csv', index=False, header=False)
    df.to_csv('./backup/{}_{}.csv'.format(now_time, score), index=False, header=False)
    
if __name__ == '__main__':
    start_time = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S"))

    main()
    
    print(time.strftime("%Y-%m-%d %H:%M:%S"))
    end_time = time.time()
    logging.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))