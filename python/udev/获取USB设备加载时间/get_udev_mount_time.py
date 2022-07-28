# -*- coding: utf-8 -*-
"""
文 件 名: get_udev_mount_time.py
文件描述: 获取USB设备加载时间
作    者: HanKin
创建日期: 2022.07.28
修改日期：2022.07.28

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger
import usb

def main():
    wmi = win32com.client.GetObject ("winmgmts:")
    for usb in wmi.InstancesOf ("Win32_USBHub"):
       logger.info(usb.DeviceID)

    print()

    for usb in wmi.InstancesOf ("win32_usbcontrollerdevice"):
        logger.info(usb.Dependent)

def debug():
    busses = usb.busses()
    for bus in busses:
        for dev in bus.devices:
            if dev.idVendor == vendor_id and dev.idProduct == product_id:
                print ("Test vehicle %s device FOUND!" %protocol)
                print ("iManufacturer   : %s" %usb.util.get_string(dev.dev, 256, 1))
                print ("iProduct            : %s" %usb.util.get_string(dev.dev, 256, 2))
                print ("iSerialNumber   : %s" %usb.util.get_string(dev.dev, 256, 3))

                return dev

    print ("Test vehicle %s device NOT FOUND!" %protocol)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    debug()
    #main()

    end_time = time.time()
    logger.info('process spend {} s.'.format(round(end_time - start_time, 3)))
    


