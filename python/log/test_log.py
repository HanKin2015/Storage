# -*- coding: utf-8 -*-
"""
文 件 名: test_log.py
文件描述: 测试log.py文件
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
from log import logger

def main():
    data = {'Name': ['xiaoming', 'zhangsan', 'lisi'], 'Age':[10, 11, 21]}
    df = pd.DataFrame(data)
    logger.info('{}'.format(df))
    logger.error('{}'.format(df))
    logger.warning('{}'.format(df))
    
    score = 87.45
    now_time = datetime.datetime.now().strftime('%m-%d-%H-%M')
    df.to_csv('./result.csv', index=False, header=False)
    df.to_csv('./backup/{}_{}.csv'.format(now_time, score), index=False, header=False)
    
    logger.warning('hello world')
    logger.debug('test test')
    
    logger.info(type(df.shape))
    logger.info([df.shape, df.shape])
    
if __name__ == '__main__':
    start_time = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S"))

    main()
    
    print(time.strftime("%Y-%m-%d %H:%M:%S"))
    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))