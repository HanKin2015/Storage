# -*- coding: utf-8 -*-
"""
文 件 名: udev_detect.py
文件描述: usb设备检测（基于windows系统）
作    者: HanKin
创建日期: 2023.02.16
修改日期：2023.02.23

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger

def print_udev_info(udev_info):
    """打印USB设备信息
    """
    
    for key, value in udev_info.items():
        logger.info('{}: {}'.format(key, value))
    return

def get_udev_info_list(wmi):
    """获取USB设备的信息列表（包含Hub和USB设备）
    """
    
    udev_info_list = []
    for usb in wmi.InstancesOf("Win32_USBHub"):
        udev_info_list.append({'usb.USBVersion': usb.USBVersion,
                             'usb.ProtocolCode': usb.ProtocolCode,
                             'usb.SubclassCode': usb.SubclassCode,
                             'usb.Availability': usb.Availability,
                             'usb.NumberOfConfigs': usb.NumberOfConfigs,
                             'usb.Name': usb.Name,
                             'usb.DeviceID': usb.DeviceID,
                             'usb.Status': usb.Status,
                             'usb.StatusInfo': usb.StatusInfo,
                             'usb.PNPDeviceID': usb.PNPDeviceID,
                             'usb.ClassCode': usb.ClassCode,
                             'usb.SystemName': usb.SystemName,
                             'usb.Caption': usb.Caption,
                             'usb.CreationClassName': usb.CreationClassName,
                             'usb.CurrentConfigValue': usb.CurrentConfigValue,
                             'usb.Description': usb.Description})
    return udev_info_list

def print_hotplug_udev_info(diff_count, udev_info_list, current_udev_info_list):
    """打印出热插拔的设备信息
    """
    
    logger.info('=============== Hotplug USB Device ===============')
    if diff_count > 0:
        udev_info_list, current_udev_info_list = current_udev_info_list, udev_info_list
    for udev_info in udev_info_list:
        if udev_info not in current_udev_info_list:
            print_udev_info(udev_info)
    logger.info('=============== Hotplug USB Device ===============')
    return

def main():
    """主函数
    """

    wmi = win32com.client.GetObject("winmgmts:")
    logger.info(wmi)  # <COMObject winmgmts:>

    udev_info_list = get_udev_info_list(wmi)
    logger.info('there are {} hub and usb devices now'.format(len(udev_info_list)))
    
    while True:
        time.sleep(1)
        
        current_udev_info_list = get_udev_info_list(wmi)
        diff_count = len(current_udev_info_list) - len(udev_info_list)
        if diff_count == 0:
            continue
        
        logger.warning('\nthere are {} usb devices which are hogplug {}'.format(abs(diff_count), 'in' if diff_count > 0 else 'out'))
        print_hotplug_udev_info(diff_count, udev_info_list, current_udev_info_list)
        udev_info_list = current_udev_info_list

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))