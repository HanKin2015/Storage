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
from log import logger

def main():
    logger.warning('hello world')
    logger.debug('test test')
    
if __name__ == '__main__':
    start_time = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S"))

    main()
    
    print(time.strftime("%Y-%m-%d %H:%M:%S"))
    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))