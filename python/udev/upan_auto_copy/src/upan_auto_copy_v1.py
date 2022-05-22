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

def argument_parser():
    """参数解析

    命令行参数解析

    Parameters
    ----------
    """
    
    parser = argparse.ArgumentParser(description='欢迎使用U盘自动拷贝文件脚本')
    #type是要传入的参数的数据类型  help是该参数的提示信息
    parser.add_argument('-u', dest='upan_path', default='E', type=str, help='U盘路径')
    parser.add_argument('-d', dest='data_path', default='./data/', type=str, help='数据路径')

    args = parser.parse_args()

    #获得传入的参数
    logging.debug('args: {}'.format(args))
    print(args)
    
    global upan_path, data_path
    upan_path = args.upan_path
    data_path = args.data_path

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
    
    data_files = []   
    for root, dirs, files in os.walk(file_dir):  
        for file in files:  
            if os.path.splitext(file)[1] == file_type_suffix:  
                data_files.append(os.path.join(root, file))  
    return data_files
    
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

    结果保留两位小数，单位为MB
    
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
    logging.debug('文件MD5值为: {}'.format(source_md5))
    print('文件MD5值为: {}'.format(source_md5))
    return True

def copy_operation(source_path, target_path, copy_opt_process):
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
    
    if is_windows:
        cmd = 'copy /Y {} {}'.format(source_path, target_path)
    else:
        cmd = 'cp -f {} {}'.format(source_path, target_path)
    logging.debug('cmd: {}'.format(cmd))
    ret = os.system(cmd)
    if ret != 0:
        logging.error('拷贝失败, cmd: {}'.format(cmd))
        return False
    
    end_time = time.time()
    copy_time = round(end_time - begin_time, 3)
    ave_speed = round(data_size  / copy_time, 3)
    logging.debug('文件大小为{}MB, {}花费{}秒, 平均速度为{}MB/s'.format(data_size, copy_opt_process, copy_time, ave_speed))
    print('文件大小为{}MB, {}花费{}秒, 平均速度为{}MB/s'.format(data_size, copy_opt_process, copy_time, ave_speed))
    
    logging.debug('文件MD5值检查中...')
    print('文件MD5值检查中...')
    if not check_md5(source_path, target_path):
        print('文件MD5值不吻合')
        logging.error('文件MD5值不吻合')
        return False
    
    # 删除源文件
    if is_windows:
        cmd = 'del /F {}'.format(source_path)
    else:
        cmd = 'rm -f {}'.format(source_path)
    logging.debug('cmd: {}'.format(cmd))
    ret = os.system(cmd)
    if ret != 0:
        logging.error('删除源文件失败, cmd: {}'.format(cmd))
        return False
    return True

def prepare_before_copy():
    """拷贝前的准备工作

    1.检测文件的存在，判断文件的类型
    2.复制源文件，不在原始文件上面进行任何操作

    Parameters
    ----------
    
    Returns
    -------
    source_path : str
        源文件路径
    target_path : str
        目标文件路径
    """
    
    # 数据文件后缀为txt文件
    data_type_suffix = '.txt'
    data_files = get_data_files(data_path, data_type_suffix)
    if len(data_files):
        # 只拷贝一个文件（按名字排序第一个）
        data_file = data_files[0]
    else:
        logging.error('数据文件夹 {} 没有 {} 类型的文件'.format(data_path, data_type_suffix))
        print('数据文件夹 {} 没有 {} 类型的文件'.format(data_path, data_type_suffix))
        return None, None
        
    # 生成一个临时文件（保护原始文件不被破坏）
    temp_data_name = data_name + 'temp'
    cmd = 'copy -f {} ./{}'.format(data_file, temp_data_name)
    if is_windows:
        data_file = data_file.replace('/', '\\')
        cmd = 'copy /Y {} .\\{}'.format(data_file, temp_data_name)
    logging.debug('cmd: {}'.format(cmd))
    ret = os.system(cmd)
    if ret != 0:
        logging.error('生成临时文件失败, cmd: {}'.format(cmd))
        return None, None

    source_path = './{}'.format(temp_data_name)
    if is_windows:
        source_path = source_path.replace('/', '\\')
        target_path = '{}:\\{}'.format(upan_path, temp_data_name)
        target_path = target_path.replace('/', '\\')
    else:
        target_path = '{}/{}'.format(upan_path, temp_data_name)
        
    logging.info('当前操作系统为: {}'.format(sys.platform))
    logging.info('源文件路径:{}, 目标文件路径:{}'.format(source_path, target_path))
    print('当前操作系统为: {}'.format(sys.platform))
    print('源文件路径:{}, 目标文件路径:{}'.format(source_path, target_path))

    global data_size
    data_size = get_file_size(source_path)
    logging.info('{}文件大小为 {} MB'.format(temp_data_name, data_size))
    print('{}文件大小为 {} MB'.format(temp_data_name, data_size))
    
    return source_path, target_path

def auto_copy():
    """自动拷贝

    将data路径下文件拷贝到目标路径

    Parameters
    ----------
    """

    copy_cnt = 1
    
    source_path, target_path = prepare_before_copy()
    if source_path is None:
        logging.error('获取源文件路径失败')
        print('获取源文件路径失败')
        return
    logging.debug('----------准备工作完成----------\n')
    print('----------准备工作完成----------\n')

    while True:
        # 当前时间
        logging.debug(time.strftime("%Y-%m-%d %H:%M:%S"))
        print(time.strftime("%Y-%m-%d %H:%M:%S"))

        logging.debug('文件{}中...'.format(local_copy_upan))
        print('文件{}中...'.format(local_copy_upan))
        # 修改文件内容（防止Windows写缓存）
        os.system("echo !a! >> {}".format(source_path))
        # 从电脑拷贝到U盘
        if not copy_operation(source_path, target_path, local_copy_upan):
            return
        
        # 睡眠1秒
        time.sleep(1)
        
        logging.debug('文件{}中...'.format(upan_copy_local))
        print('文件{}中...'.format(upan_copy_local))
        # 修改文件内容（防止Windows写缓存）
        os.system("echo !a! >> {}".format(target_path))
        # 从U盘拷贝到电脑
        if not copy_operation(target_path, source_path, upan_copy_local):
            return
        
        logging.debug('----------第{}次拷贝完成----------\n'.format(copy_cnt))
        print('----------第{}次拷贝完成----------\n'.format(copy_cnt))
        if copy_cnt % 10 == 0:
            logging.info('第{}次拷贝完成'.format(copy_cnt))
        if copy_cnt % 1000 == 0:
            global data_size
            data_size = get_file_size(source_path)
            logging.info('拷贝{}次后文件大小为 {} MB'.format(copy_cnt, data_size))
        copy_cnt += 1
        
        # 睡眠1秒
        time.sleep(1)

def main():
    argument_parser()
    auto_copy()

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