# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_copy_v2.py
文件描述: U盘自动拷贝文件(在电脑上面运行)
作    者: HanKin
创建日期: 2022.02.15
修改日期：2022.04.06

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

# U盘路径
upan_path = 'E'

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

def check_md5(source_path, target_path):
    """检查文件md5值

    判断文件拷贝是否正确
    
    Parameters
    ------------
    source_path : str
        源文件路径
    target_path : str
        目标文件路径
        
    Returns
    -------
    bool
        成功True, 失败False
    """
    
    source_md5 = get_file_md5(source_path)
    target_md5 = get_file_md5(target_path)
    if source_md5 != target_md5:
        logging.error('文件md5值不吻合, source: {} target: {}'.format(source_md5, target_md5))
        return False
    return True

def copy_operation(source_path, target_path):
    """拷贝操作

    使用Windows的copy命令进行拷贝
    /Y 不使用确认是否要改写现有目标文件 的提示。
    
    Parameters
    ------------
    source_path : str
        源文件路径
    target_path : str
        目标文件路径
        
    Returns
    -------
    bool
        成功True, 失败False
    """
    
    begin_time = time.time()
    
    cmd = 'copy /Y {} {}'.format(source_path, target_path)
    ret = os.system(cmd)
    if ret != 0:
        logging.error('拷贝失败, cmd: {}'.format(cmd))
        return False
    
    end_time = time.time()
    copy_time = round(end_time - begin_time, 3)
    ave_speed = round(data_size  / copy_time, 3)
    print('拷贝花费{}秒, 平均拷贝速度为{}MB/s'.format(copy_time, ave_speed))
    
    if not check_md5(source_path, target_path):
        print('文件md5值不吻合')
        return False
    
    cmd = 'del {}'.format(source_path)
    ret = os.system(cmd)
    if ret != 0:
        logging.error('删除源文件失败, cmd: {}'.format(cmd))
        return False
    return True

def auto_copy():
    """自动拷贝

    将data路径下文件拷贝到目标路径

    Parameters
    ----------
    """

    copy_cnt = 1
    
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
        
        source_path = '.\\{}'.format(temp_data_name)
        target_path = '{}:\\{}'.format(upan_path, temp_data_name)

        # 从电脑拷贝到U盘
        if not copy_operation(source_path, target_path):
            return
            
        time.sleep(3)

        # 从U盘拷贝到电脑
        if not copy_operation(target_path, source_path):
            return
        
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