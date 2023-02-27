# -*- coding: utf-8 -*-
"""
文 件 名: wmi_usb_example.py
文件描述: wmi操作usb设备例子
作    者: HanKin
创建日期: 2023.02.16
修改日期：2023.02.16

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger

def main():
    """主函数
    """

    wmi = win32com.client.GetObject("winmgmts:")
    logger.info(wmi)  # <COMObject winmgmts:>

    # 系统的所有PnP设备
    logger.info("===================Win32_PnPEntity=================")   
    count = 0
    for pnp in wmi.InstancesOf('Win32_PnPEntity'):
            logger.debug('pnp.Name: {}'.format(pnp.Name))
            logger.debug('pnp.DeviceID: {}'.format(pnp.DeviceID))
            logger.debug('pnp.Status: {}'.format(pnp.Status))
            logger.debug('pnp.Description: {}\n'.format(pnp.Description))
            count += 1
    logger.info('there are {} PnP devices'.format(count))

    # USB主控（UHCI、EHCI、XHCI）以及主控上面的USB设备
    logger.info("===================win32_usbcontrollerdevice=================")
    count = 0
    for usb in wmi.InstancesOf("win32_usbcontrollerdevice"):
        logger.debug('usb.Dependent: {}'.format(usb.Dependent))
        logger.debug('usb.AccessState: {}'.format(usb.AccessState))
        logger.debug('usb.Antecedent: {}'.format(usb.Antecedent))
        logger.debug('usb.NegotiatedSpeed: {}\n'.format(usb.NegotiatedSpeed))
        count += 1
    logger.info('there are {} usbcontroller devices'.format(count))

    # USB主控，即UHCI、EHCI、XHCI
    logger.info("===================win32_usbcontroller=================")
    count = 0
    for usb in wmi.InstancesOf("win32_usbcontroller"):
        logger.debug('usb.Name: {}'.format(usb.Name))
        logger.debug('usb.DeviceID: {}'.format(usb.DeviceID))
        logger.debug('usb.Status: {}'.format(usb.Status))
        logger.debug('usb.StatusInfo: {}'.format(usb.StatusInfo))
        logger.debug('usb.Description: {}\n'.format(usb.Description))
        count += 1
    logger.info('there are {} usbcontrollers'.format(count))

    # USBHub以及加载的USB设备
    logger.info("===================Win32_USBHub=================")
    count = 0
    for usb in wmi.InstancesOf("Win32_USBHub"):
        logger.info('usb.USBVersion: {}'.format(usb.USBVersion))
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
        logger.info('usb.Description: {}\n'.format(usb.Description))
        count += 1
    logger.info('there are {} hub and usb devices'.format(count))

    # 串口设备
    logger.info("===================Win32_SerialPort=================")
    count = 0
    for usb in wmi.InstancesOf("Win32_SerialPort"):
        # https://learn.microsoft.com/en-us/windows/win32/cimwin32prov/win32-serialport
        # https://cloud.tencent.com/developer/ask/sof/1442270
        # https://docs.microsoft.com/en-us/windows/win32/cimwin32prov/win32-processor
        
        #print(usb)
        #print(type(usb))
        #print(usb.__dict__)
        #print(dir(usb))
        #print(vars(usb))
        #for name in dir(usb) :
        #    value = getattr(usb, name)
        #    doc = (value.__doc__ or '').split('.', 1)[0]
        #    print('MEMBER: %s\nDOCSTRING: %s\n\n' % (name, doc))
        print(usb.Availability)
        #print(help(usb))
        #print(globals())
        logger.info('usb.Name: {}'.format(usb.Name))
        logger.info('usb.DeviceID: {}'.format(usb.DeviceID))
        logger.info('usb.Status: {}'.format(usb.Status))
        logger.info('usb.StatusInfo: {}'.format(usb.StatusInfo))
        logger.info('usb.SystemName: {}'.format(usb.SystemName))
        logger.info('usb.Caption: {}'.format(usb.Caption))
        logger.info('usb.PNPDeviceID: {}'.format(usb.PNPDeviceID))
        logger.info('usb.CreationClassName: {}'.format(usb.CreationClassName))
        logger.info('usb.Description: {}\n'.format(usb.Description))
        count += 1
    logger.info('there are {} com devices'.format(count))

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))