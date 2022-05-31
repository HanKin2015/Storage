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
logger = logging.getLogger()
logger.setLevel(logging.INFO)  # Log等级总开关
log_file_abs = "./log/process.log"
 
stream_handler = logging.StreamHandler()  # 日志控制台输出
 
handler = logging.FileHandler(log_file_abs, mode='a', encoding='UTF-8')  # 日志文件输出
handler.setLevel(logging.DEBUG)
 
# 控制台输出格式
stream_format = logging.Formatter("%(asctime)s - %(pathname)s[line:%(lineno)d] - %(levelname)s: %(message)s")
 
# 文件输出格式
logging_format = logging.Formatter(
    '%(asctime)s - %(pathname)s - %(funcName)s - %(lineno)s - %(levelname)s: %(message)s')
 
handler.setFormatter(logging_format)  # 为改处理器handler 选择一个格式化器
stream_handler.setFormatter(stream_format)
 
logger.addHandler(handler)  # 为记录器添加 处理方式Handler
logger.addHandler(stream_handler)

# 开启debug日志方法（创建一个debug文件即可）
if os.path.exists('./log/debug'):
    logger.setLevel(logging.DEBUG)

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
    
if __name__ == '__main__':
    start_time = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S"))

    main()
    
    print(time.strftime("%Y-%m-%d %H:%M:%S"))
    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))