# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_copy.py
文件描述: U盘自动拷贝文件(在电脑上面运行)
作    者: HanKin
创建日期: 2022.02.15
修改日期：2022.04.25

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
data_size = 1024    # 单位MB，即1GB大小文件

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

# 配置日志
file_handler = logging.FileHandler(log_file, encoding='utf-8') 
logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S',
                    handlers={file_handler})

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
    parser.add_argument('-u', dest='upan_path', default='D', type=str, help='U盘路径')
    parser.add_argument('-s', dest='data_size', default='1024', type=int, help='数据文件大小(MB)')

    args = parser.parse_args()

    #获得传入的参数
    logging.debug('args: {}'.format(args))
    print(args)
    
    global upan_path, data_size
    upan_path = args.upan_path
    data_size = args.data_size

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

def generate_data_file(source_path, data_size):
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
    
    fp = open(source_path, 'w', encoding='utf-8')
    fp.seek(1024*1024*data_size)
    random_content = str(round(random.uniform(0, 1000), 3))
    fp.write(random_content)
    fp.close()
    
    end_time = time.time()
    copy_time = round(end_time - begin_time, 3)
    ave_speed = round(data_size  / copy_time, 3)
    logging.debug('文件大小为{}MB, 生成数据文件花费{}秒, 平均速度为{}MB/s'.format(data_size, copy_time, ave_speed))
    print('文件大小为{}MB, 生成数据文件花费{}秒, 平均速度为{}MB/s'.format(data_size, copy_time, ave_speed))

def auto_copy():
    """自动拷贝

    将data路径下文件拷贝到目标路径

    Parameters
    ----------
    """

    copy_cnt = 1

    while True:
        # 当前时间
        logging.debug(time.strftime("%Y-%m-%d %H:%M:%S"))
        print(time.strftime("%Y-%m-%d %H:%M:%S"))

            
        local_time = time.strftime("%Y%m%d%H%M%S", time.localtime())
        data_name = '{}.txt'.format(str(local_time))
        if is_windows:
            source_path = '{}:\\{}'.format(upan_path, data_name)
            target_path = '.\\{}'.format(data_name)
        else:
            source_path = '{}/{}'.format(upan_path, data_name)
            target_path = './{}'.format(data_name)
        
        logging.debug('{}文件随机生成中...'.format(source_path))
        print('{}文件随机生成中...'.format(source_path))
        generate_data_file(source_path, data_size)

        logging.debug('文件{}中...'.format(upan_copy_local))
        print('文件{}中...'.format(upan_copy_local))
        # 从U盘拷贝到电脑
        if not copy_operation(source_path, target_path, upan_copy_local):
            return

        # 睡眠1秒
        time.sleep(1)
        
        logging.debug('文件{}中...'.format(local_copy_upan))
        print('文件{}中...'.format(local_copy_upan))
        # 从电脑拷贝到U盘
        if not copy_operation(target_path, source_path, local_copy_upan):
            return
        # 删除源文件
        if is_windows:
            cmd = 'del /F {}'.format(source_path)
        else:
            cmd = 'rm -f {}'.format(source_path)
        logging.debug('cmd: {}'.format(cmd))
        ret = os.system(cmd)
        if ret != 0:
            logging.error('删除源文件失败, cmd: {}'.format(cmd))
        
        logging.debug('----------第{}次拷贝完成----------\n'.format(copy_cnt))
        print('----------第{}次拷贝完成----------\n'.format(copy_cnt))
        if copy_cnt % 10 == 0:
            logging.info('第{}次拷贝完成'.format(copy_cnt))
        copy_cnt += 1
        
        # 睡眠1秒
        time.sleep(1)

def main():
    argument_parser()
    auto_copy()

if __name__ == '__main__':
    os.system('chcp 936 & cls')
    logging.info('------U盘自动拷贝程序开始------')
    try:
        main()
    except KeyboardInterrupt as err:
        # 注意，协程except Exception将无法捕获KeyboardInterrupt异常
        # 打印err为空
        logging.warning('捕获到KeyboardInterrupt异常')
        print('捕获到KeyboardInterrupt异常')
    #except Exception as err:
    #    logging.error('捕获到异常, {}'.format(err))
    #    print('捕获到异常, {}'.format(err))
    logging.info('------U盘自动拷贝程序结束------')