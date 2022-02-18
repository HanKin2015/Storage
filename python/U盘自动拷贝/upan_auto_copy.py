# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_copy_v2.py
文件描述: U盘自动拷贝文件(在电脑上面运行)
作    者: HanKin
创建日期: 2022.02.15
修改日期：2022.02.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import argparse
import logging
import hashlib

# 日志路径
log_path = '.\\log\\'
log_name = 'upan_auto_copy.log'
log_file = log_path + log_name

# 数据路径
data_path = '.\\data\\'
data_name = '1.txt'
data_size = 1024    # 单位MB
data_file = data_path + data_name

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

# U盘路径
upan_path = 'E'

def argument_parser():
    """参数解析

    命令行参数解析

    Parameters
    ----------
    """
    
    parser = argparse.ArgumentParser(description='欢迎使用U盘自动拷贝文件脚本')
    #type是要传入的参数的数据类型  help是该参数的提示信息
    parser.add_argument('upan_path', type=str, help='U盘路径')
    #parser.add_argument('file_size', type=str, help='U盘路径')

    args = parser.parse_args()

    #获得传入的参数
    print(args)

def get_file_md5(file_path):
    """获取文件md5值

    通过hashlib库计算文件的md5值
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的md5值
    """

    m = hashlib.md5()   #创建md5对象
    with open(file_path,'rb') as fobj:
        while True:
            data = fobj.read(4096)
            if not data:
                break
            m.update(data)  #更新md5对象

    return m.hexdigest()    #返回md5值

def get_file_size(file_path):
    """获取文件的大小

    结果保留两位小数，单位为KB
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的大小
    """

    file_size = os.path.getsize(file_path)
    file_size = file_size / float(1024)
    return round(file_size, 2)

def auto_copy():
    """自动拷贝

    将data路径下文件拷贝到目标路径

    Parameters
    ----------
    """

    copy_cnt = 1
    target_path = upan_path
    
    # 生成一个临时文件
    temp_data_name = data_name + 'temp'
    cmd = 'copy /Y {} .\\{}'.format(data_file, temp_data_name)
    ret = os.system(cmd)
    if ret != 0:
        logging.error('生成临时文件失败, cmd: {}'.format(cmd))
        return
    
    logging.info('------拷贝开始------')
    while True:
        # 当前时间
        print(time.strftime("%Y-%m-%d %H:%M:%S"))
    
        # 生成新文件名（增加时间序号）
        new_data_name = data_name + str(int(time.time()))
        #print(new_data_name)
        
        # 重命名文件
        cmd = 'rename .\\{} {}'.format(temp_data_name, new_data_name)
        ret = os.system(cmd)
        if ret != 0:
            logging.error('重命名文件失败, cmd: {}'.format(cmd))
            return
        temp_data_name = new_data_name
        
        # 获取源文件md5值
        source_md5 = get_file_md5(temp_data_name)

        # 从电脑拷贝到U盘
        begin_time = time.time()
        cmd = 'copy /Y .\\{} {}:\\'.format(temp_data_name, target_path)
        ret = os.system(cmd)
        end_time = time.time()
        copy_time = round(end_time - begin_time, 3)
        ave_speed = round(data_size  / copy_time, 3)
        print('从电脑拷贝到U盘拷贝花费{}秒, 平均拷贝速度为{}MB/s'.format(copy_time, ave_speed))
        
        os.system("del {}".format(temp_data_name))
        if ret != 0:
            logging.error('从电脑拷贝到U盘失败, cmd: {}'.format(cmd))
            break

        # 获取目标文件md5值
        target_data_path = '{}:\\{}'.format(target_path, temp_data_name)
        target_md5 = get_file_md5(target_data_path)

        # 判断md5值是否吻合
        if source_md5 != target_md5:
            logging.error('从电脑拷贝到U盘, 文件md5值不吻合, source: {} target: {}'.format(source_md5, target_md5))
            break
            
        time.sleep(3)

        # 从U盘拷贝到电脑
        begin_time = time.time()
        source_md5 = target_md5
        cmd = 'copy /Y {}:\\{} .\\'.format(target_path, temp_data_name)
        ret = os.system(cmd)
        end_time = time.time()
        copy_time = round(end_time - begin_time, 3)
        ave_speed = round(1024  / copy_time, 3)
        print('从U盘拷贝到电脑拷贝花费{}秒, 平均拷贝速度为{}MB/s'.format(copy_time, ave_speed))
        
        os.system('del {}:\\{}'.format(target_path, temp_data_name))
        if ret != 0:
            logging.error('从U盘拷贝到电脑失败, cmd: {}'.format(cmd))
            break
        
        target_md5 = get_file_md5(temp_data_name)
        
        # 判断md5值是否吻合
        if source_md5 != target_md5:
            logging.error('从U盘拷贝到电脑, 文件md5值不吻合, source:{} target:{}'.format(source_md5, target_md5))
            break
        
        print('第{}次拷贝完成\n'.format(copy_cnt))
        if copy_cnt % 10 == 0:
            logging.info('第{}次拷贝完成'.format(copy_cnt))
        copy_cnt += 1
    
    logging.info('------拷贝结束------\n')

def main():
    #argument_parser()
    auto_copy()

if __name__ == '__main__':
    main()