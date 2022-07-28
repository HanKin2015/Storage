# -*- coding: utf-8 -*-
"""
文 件 名: calc_upan_mount_time.py
文件描述: 记录U盘插入加载时间(在电脑上面运行)
备    注: 通过能获取到高拍仪 
作    者: HanKin
创建日期: 2022.04.11
修改日期：2022.04.11

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import argparse
import logging

# 日志路径
log_path = './log/'
log_name = 'record_video_mount_time.log'
log_file = log_path + log_name

# 是否为Windows系统
is_windows = False
if sys.platform == 'win32' or sys.platform == 'win64':
    is_windows = True

# api接口
AMCAP_API_TOOL = "amcap_api.exe"

# 获取高拍仪摄像头分辨率接口
VIDEO_INFO_TOOL = "getvideoinfo.exe"

# 建立必要的文件夹
if not os.path.exists(log_path):
    os.makedirs(log_path)

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

    parser = argparse.ArgumentParser(description='欢迎使用记录高拍仪摄像头映射挂载时间脚本')
    #type是要传入的参数的数据类型  help是该参数的提示信息
    #parser.add_argument('-u', dest='upan_path', default='E', type=str, help='U盘路径')

    args = parser.parse_args()

    #获得传入的参数
    print(args)

def run_cmd(cmd):
    ret_obj = os.popen(cmd)
    ret = ret_obj.read()
    ret_obj.close
    return ret

# 只是简单的timeout时间是不准确的，命令必须是执行速度比较快的
def wait_cmd_success_timeout(cmd, timeout, interval=0.2):
    second = 0
    ret = 0
    while True:
        ret = os.system(cmd)
        resolution_ret = run_cmd(cmd)
        if "MEDIASUBTYPE" in resolution_ret and "devicename" in resolution_ret:
            break
        else:
            print("未获取到高拍仪设备，请检查是否接入")

        time.sleep(interval)
        
        second += interval
        if second >= timeout:
            break
    return ret

# 插入高拍仪摄像头记录映射挂载时间。如果返回-1代表映射超时失败，成功返回0
def calc_video_mount_time():
    print('当前操作系统为: {}'.format(sys.platform))
    
    if is_windows:
        cmd = VIDEO_INFO_TOOL

    ret = wait_cmd_success_timeout(cmd, 40)
    if ret != 0:
        return -1

    # 当前时间
    print('高拍仪/摄像头加载完成时间: {}'.format(time.strftime("%Y-%m-%d %H:%M:%S")))
    return 0

def main():
    argument_parser()
    calc_video_mount_time()

if __name__ == '__main__':
    main()