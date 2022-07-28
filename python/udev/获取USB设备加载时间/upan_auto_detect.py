# -*- coding: utf-8 -*-
"""
文 件 名: upan_auto_detect.py
文件描述: U盘自动检测加载完成时间(在电脑上面运行)
备    注: 这个是网上版本未做修改，优点在于不需要指定盘符
作    者: HanKin
创建日期: 2022.04.08
修改日期：2022.04.08

Copyright (c) 2022 HanKin. All rights reserved.
"""

from time import sleep
from shutil import copytree
from psutil import disk_partitions
import sys
#pip3 install psutil 
 
print_debug=0
   
# U盘发现问题  开机启动问题  视频测试 循环问题
def USB_PathList():
    driver_= sys.platform
    usb_id_path=''
    usb_path="nopath"
     
    if driver_ == "win32" or driver_ == "win64":
        usb_id_path='removable'
        #  检测所有的驱动器，进行遍历寻找哦
        for item in disk_partitions():
            print(item)
            if usb_id_path in item.opts:
                path,driver = item.device, item.opts
                #  输出可移动驱动器符号
                if print_debug:print('发现usb驱动：', driver," -路径- ",path)
                usb_path=path
                return usb_path
            #  没有找到可输出驱动器
            else:
                if print_debug:print('没有找到可移动驱动器')
                #return "nopath"
                continue
 
    else:
        usb_id_path='/media/'
        #  检测所有的驱动器，进行遍历寻找哦
        for item in disk_partitions():
            print(item)
            if usb_id_path in item.mountpoint:
                driver, path = item.device, item.mountpoint
                #  输出可移动驱动器符号
                if print_debug:print('发现usb驱动：', driver," -路径- ",path)
                usb_path=path
                return usb_path
            #  没有找到可输出驱动器
            else:
                if print_debug:print('没有找到可移动驱动器')
                continue

    print(usb_path)
    return usb_path
 
if __name__ == "__main__":
    while True:
        sleep(1)
        path_t=USB_PathList()
        print(path_t)
 