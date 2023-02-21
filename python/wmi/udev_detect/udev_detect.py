# -*- coding: utf-8 -*-
"""
文 件 名: udev_detect.py
文件描述: usb设备检测（基于windows系统）
作    者: HanKin
创建日期: 2023.02.16
修改日期：2023.02.16

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger

def get_current_hub_and_udev_count(wmi):
    """获取当前hub和usb设备数量
    """
    
    return len(wmi.InstancesOf("Win32_USBHub"))

def print_current_udev_info(wmi):
    """打印当前usb设备信息
    """
    
    # USBHub以及加载的USB设备
    logger.info("===================Win32_USBHub=================")
    count = 0
    for usb in wmi.InstancesOf("Win32_USBHub"):
        if usb.Name != 'USB Root Hub':
            if count == 0:
                logger.info('usb.USBVersion: {}'.format(usb.USBVersion))
            else:
                logger.info('\nusb.USBVersion: {}'.format(usb.USBVersion))
            logger.info('usb.ProtocolCode: {}'.format(usb.ProtocolCode))
            logger.info('usb.SubclassCode: {}'.format(usb.SubclassCode))
            logger.info('usb.Availability: {}'.format(usb.Availability))
            logger.info('usb.NumberOfConfigs: {}'.format(usb.NumberOfConfigs))
            logger.info('usb.Name: {}'.format(usb.Name))
            logger.info('usb.DeviceID: {}'.format(usb.DeviceID))
            logger.info('usb.Status: {}'.format(usb.Status))
            logger.info('usb.StatusInfo: {}'.format(usb.StatusInfo))
            logger.info('usb.PNPDeviceID: {}'.format(usb.PNPDeviceID))
            logger.info('usb.ClassCode: {}'.format(usb.ClassCode))
            logger.info('usb.SystemName: {}'.format(usb.SystemName))
            logger.info('usb.Caption: {}'.format(usb.Caption))
            logger.info('usb.CreationClassName: {}'.format(usb.CreationClassName))
            logger.info('usb.CurrentConfigValue: {}'.format(usb.CurrentConfigValue))
            logger.info('usb.Description: {}'.format(usb.Description))
            count += 1
    logger.info('there are {} usb devices'.format(count))
    logger.info("===================Win32_USBHub=================")

def main():
    """主函数
    """

    wmi = win32com.client.GetObject("winmgmts:")
    logger.info(wmi)  # <COMObject winmgmts:>

    hub_udev_count = get_current_hub_and_udev_count(wmi)
    logger.info('there are {} hub and usb devices now'.format(hub_udev_count))
    
    while True:
        current_hub_udev_count = get_current_hub_and_udev_count(wmi)
        if current_hub_udev_count > hub_udev_count:
            logger.warning('there is a new usb device')
            print_current_udev_info(wmi)
        elif current_hub_udev_count < hub_udev_count:
            logger.warning('there is a usb device which is hotplug out')
        hub_udev_count = current_hub_udev_count
        time.sleep(1)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))