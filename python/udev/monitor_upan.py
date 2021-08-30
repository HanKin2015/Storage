# -*- coding: utf-8 -*-
"""
文 件 名: monitor_upan.py
文件描述: psutil是一个跨平台库，能够轻松实现获取系统运行的进程和系统利用率（包括CPU、内存、磁盘、网络等）信息。它主要用来做系统监控，性能分析，进程管理。
作    者: HanKin
创建日期: 2021.08.30
修改日期：2021.08.30

Copyright (c) 2021 HanKin. All rights reserved.
"""
import psutil
import sys
import os
import time
from datetime import datetime

mobile = ""  # 移动设备盘符

# 储存当前盘的盘符
def updata():
    global mobile_letter
    try:
        part = psutil.disk_partitions()
    except:
        sys.exit(-1)
    else:
        # 驱动器分类
        for i in range(len(part)):
            tmplist = part[i].opts.split(",")
            if "fixed" in tmplist:      # 本地设备
                pass
            elif "cdrom" in tmplist:    # CD设备
                pass
            else:
                # U盘
                mobile = part[i].device[:2]
                break

# 读取U盘并复制到指定位置
def copy_file_to_disk_hidden(USB_path):
    # U盘的盘符
    usb_path = USB_path + "/"
    # 要复制到的路径
    mkdir("D:/usb_io/")
    save_path = "D:/usb_io/" + datetime.now().strftime("%Y%m%d_%H%M%S") + ".txt"
    f = open(save_path, "w", encoding='utf-8')
    # 复制U盘的内容名称
    while True:
        if os.path.exists(usb_path): 
            filelist=[]
            filenames = os.listdir(USB_path)
            for fn in filenames:
                fullfilename = os.path.join(USB_path, fn)     
                filelist.append(fullfilename)
            for j in filelist:
                f.write(str(j) + '\n')
            break
        else:
            time.sleep(1)
    f.close()
   
#创建指定位置    
def mkdir(path):
    isExists=os.path.exists(path)
    #判断结果
    if not isExists:
        #创建目录操作函数
        os.makedirs(path)
        return True
    else:
        #如果目录存在则不创建
        return False   

if __name__ == "__main__":
    check_times = 0
    
    #读取驱动器信息
    while True:
        check_times += 1
        print('第{}次读取驱动器信息...'.format(check_times))
        updata()
        if mobile != "":
            copy_file_to_disk_hidden(mobile)
            time.sleep(10)
        else:
            print('未检测到U盘设备')
            time.sleep(5)


