# -*- coding: utf-8 -*-
"""
文 件 名: generate_any_size_file.py
文件描述: 生成任意大小的文件
作    者: HanKin
创建日期: 2022.06.14
修改日期：2022.06.14

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import argparse
import hashlib
import random

content   = ' '
file_size = 1024

# 是否为Windows系统
is_windows = False
if sys.platform == 'win32' or sys.platform == 'win64':
    is_windows = True
    
def argument_parser():
    """参数解析

    命令行参数解析

    Parameters
    ----------
    """
    
    parser = argparse.ArgumentParser(description='欢迎使用生成任意大小文件脚本')
    #type是要传入的参数的数据类型  help是该参数的提示信息
    parser.add_argument('-c', dest='content', default=' ', type=str, help='数据内容(单字符)')
    parser.add_argument('-s', dest='file_size', default='1024', type=int, help='数据文件大小(MB)')

    args = parser.parse_args()

    #获得传入的参数
    print('args: {}'.format(args))
    
    global content, file_size
    content = args.content
    file_size = args.file_size

def generate_null_data_file(file_name):
    """生成数据文件

    seek() 方法用于移动文件读取指针到指定位置。
    
    Parameters
    ------------
    source_path : str
        源文件路径
    data_size : int
        源文件大小
        
    Returns
    -------
    bool
        成功True, 失败False
    """
    
    begin_time = time.time()
    
    fp = open(file_name, 'w', encoding='utf-8')
    fp.seek(1024*1024*file_size)
    random_content = str(round(random.uniform(0, 1000), 3))
    fp.write(random_content)
    fp.close()
    
    end_time = time.time()
    gen_time = round(end_time - begin_time, 3)
    ave_speed = round(file_size  / gen_time, 3)
    print('文件大小为{}MB, 生成数据文件花费{}秒, 平均速度为{}MB/s'.format(file_size, gen_time, ave_speed))

def generate_data_file(file_name):
    """
    """
    
    begin_time = time.time()

    print('正在生成TXT文件，请稍候... ...')
    f = open(file_name, 'w')
    for i in range(file_size):
        if i >= 100:
            if i % 100 == 0:
                print(f'已生成{i//100 * 100}MB数据.')
        for j in range(1024):
            try:
                f.write(content * 1024)
            except KeyboardInterrupt:
                print('\n异常中断:KeyboardInterrupt')
                f.close()
                exit(-1)
    f.close()
    
    end_time = time.time()
    gen_time = round(end_time - begin_time, 3)
    ave_speed = round(file_size  / gen_time, 3)
    print('文件大小为{}MB, 生成数据文件花费{}秒, 平均速度为{}MB/s'.format(file_size, gen_time, ave_speed))

def main():
    argument_parser()
    
    print(time.strftime("%Y-%m-%d %H:%M:%S"))
    local_time = time.strftime("%Y%m%d%H%M%S", time.localtime())
    file_name = '{}.txt'.format(str(local_time))
    if content == ' ':
        generate_null_data_file(file_name)
    else:
        generate_data_file(file_name)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt as err:
        # 注意，协程except Exception将无法捕获KeyboardInterrupt异常
        # 打印err为空
        print('捕获到KeyboardInterrupt异常')
    except Exception as err:
        print('捕获到异常, {}'.format(err))