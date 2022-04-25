# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_copy.py
文件描述: U盘自动拷贝文件(在电脑上面运行)
作    者: HanKin
创建日期: 2022.02.15
修改日期：2022.04.24

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import argparse
import logging
import hashlib
import random

# 日志路径
log_path = './log/'
log_name = 'upan_auto_copy.log'
log_file = log_path + log_name

# 数据路径
data_path = './data/'
data_name = '1.txt'
data_size = 1024    # 单位MB
data_file = data_path + data_name

# U盘盘符
upan_path = 'E'

# 是否为Windows系统
is_windows = False
if sys.platform == 'win32' or sys.platform == 'win64':
    is_windows = True
    
# 拷贝操作过程
upan_copy_local = '从U盘拷贝到电脑'
local_copy_upan = '从电脑拷贝到U盘'

# 建立必要的文件夹
if not os.path.exists(log_path):
    os.makedirs(log_path)
if not os.path.exists(data_path):
    os.makedirs(data_path)

# 配置日志
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S',
                    filename=log_file,
                    filemode='a')

# 开启debug日志方法（创建一个debug文件即可）
if os.path.exists('debug'):
    logging.getLogger().setLevel(logging.DEBUG)

def generate_file1(n):
    local_time = time.strftime("%Y%m%d%H%M%S", time.localtime())
    file_name = 'M:\\{}.txt'.format(str(local_time))
    big_file= open(file_name, 'w', encoding='utf-8')
    big_file.seek(1024*1024*n)
    random_content = str(round(random.uniform(0, 1000), 1))
    big_file.write(random_content)
    big_file.close()

def generate_file2():
    f = open('input.txt', 'w')

    nlines = 100000
    col = 50

    for i in range(nlines):
        nums = [str(round(random.uniform(0, 1000), 1)) for j in range(col)]
        f.write(' '.join(nums))
        f.write('\n')

    f.close()

def main():
    #argument_parser()
    #auto_copy()
    begin_time = time.time()
    generate_file1(200)
    #generate_file2()
    end_time = time.time()
    copy_time = round(end_time - begin_time, 3)
    print('花费 {} s'.format(copy_time))

if __name__ == '__main__':
    logging.info('------U盘自动拷贝程序开始------')
    try:
        main()
    except KeyboardInterrupt as err:
        # 注意，协程except Exception将无法捕获KeyboardInterrupt异常
        # 打印err为空
        logging.warning('捕获到KeyboardInterrupt异常')
        print('捕获到KeyboardInterrupt异常')
    except Exception as err:
        logging.error('捕获到异常, {}'.format(err))
        print('捕获到异常, {}'.format(err))
    logging.info('------U盘自动拷贝程序结束------')