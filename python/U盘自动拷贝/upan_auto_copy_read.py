# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_copy_read.py
文件描述: U盘自动拷贝文件读取U盘(在电脑上面运行)
改    进: 1.文件名不固定，data目录下即可
          2.文件位置不固定，默认data，可以参数指定
          3.U盘符位置不固定，默认E盘，可以参数指定
作    者: HanKin
创建日期: 2022.04.06
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
data_path = 'E:\\data\\'
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
    
    parser = argparse.ArgumentParser(description='欢迎使用U盘自动写入文件脚本')
    #type是要传入的参数的数据类型  help是该参数的提示信息
    parser.add_argument('-u', dest='upan_path', default='E', type=str, help='U盘路径')
    parser.add_argument('-d', dest='data_path', default='.\\data\\', type=str, help='数据路径')

    args = parser.parse_args()

    #获得传入的参数
    print(args)
    
    global upan_path, data_path
    upan_path = args.upan_path
    data_path = '{}:\\data\\'.format(args.upan_path)

def get_data_files(file_dir, file_type_suffix='.txt'):
    """获取文件夹中的指定类型的文件名及路径
    
    深度为1
    
    Parameters
    ------------
    file_dir : str
        文件夹路径
    file_type_suffix : str
        文件类型后缀

    Returns
    -------
    list
        返回文件的md5值
    """
    
    files_path = []   
    for root, dirs, files in os.walk(file_dir):  
        for file in files:  
            if os.path.splitext(file)[1] == file_type_suffix:  
                files_path.append(os.path.join(root, file))  
    return files_path

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
    file_size = file_size / float(1024) / float(1024)
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
    
    print('文件md5值检查中...')
    if not check_md5(source_path, target_path):
        print('文件md5值不吻合')
        return False
    
    # 单向拷贝就删除目标文件
    cmd = 'del {}'.format(target_path)
    ret = os.system(cmd)
    if ret != 0:
        logging.error('删除目标文件失败, cmd: {}'.format(cmd))
        return False
    return True

def auto_copy_read():
    """从U盘拷贝到电脑

    将data路径下文件拷贝到目标路径

    Parameters
    ----------
    """

    copy_cnt = 1

    data_type_suffix = '.txt'
    data_files = get_data_files(data_path, data_type_suffix)
    if len(data_files):
        source_path = data_files[0]
    else:
        print('数据文件夹 {} 没有 {} 类型的文件'.format(data_path, data_type_suffix))
        return
    target_path = '.\\{}'.format(data_name)
    print('源文件路径:{}, 目标文件路径:{}'.format(source_path, target_path))

    global data_size
    data_size = get_file_size(source_path)
    print('文件大小为 {} MB'.format(data_size))
    
    logging.info('------拷贝开始------')
    while True:
        # 当前时间
        print(time.strftime("%Y-%m-%d %H:%M:%S"))

        # 从U盘拷贝到电脑
        if not copy_operation(source_path, target_path):
            return
        
        print('第{}次拷贝完成\n'.format(copy_cnt))
        if copy_cnt % 10 == 0:
            logging.info('第{}次拷贝完成'.format(copy_cnt))
        copy_cnt += 1
        
        # 睡眠2秒
        time.sleep(2)
    
    logging.info('------拷贝结束------\n')

def main():
    argument_parser()
    auto_copy_read()

if __name__ == '__main__':
    main()