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
from usb.core import USBError
import usb.backend.libusb0
import usb.backend.libusb1
import os

def main():
    wmi = win32com.client.GetObject ("winmgmts:")
    for usb in wmi.InstancesOf ("Win32_USBHub"):
       logger.info(usb.DeviceID)

    print()

    for usb in wmi.InstancesOf ("win32_usbcontrollerdevice"):
        logger.info(usb.Dependent)

def get_usb_devices(backend):
    '''
    Get USB devices

    @return: list of tuples (dev_idVendor, dev_idProduct, dev_name)
    '''
    
    #backend = usb.backend.libusb0.get_backend(find_library=lambda x: 'D:\\Github\\Storage\\python\\udev\\U盘自动拷贝\\libusb\\amd64\\libusb0.dll')

    return [(device.idVendor, device.idProduct, _get_dev_string_info(device)) 
                for device in usb.core.find(find_all=True, backend=backend)
                    if device.idProduct > 2]

def test():
    logger.info(usb.core.show_devices())
    devices = usb.core.find(find_all=True)
    
    while True:
        try:
            # 获得下一个值:
            dev = next(devices)
            print("device bus:", dev.bus)
            print("device address:", dev.address)
            print("device port:", dev.port_number)
            print("device speed:", dev.speed)
        except StopIteration:
            # 遇到StopIteration就退出循环
            break
    logger.info('test is over')

def debug():
    libusb_dll_path = os.getcwd()+'/libusb-1.0.dll'
    logger.info('libusb_dll_path: {}'.format(libusb_dll_path))
    if not os.path.exists(libusb_dll_path):
        logger.error('libusb dll file not exists')
        #return
    
    # 为啥不能直接写成字符串
    #backend = usb.backend.libusb0.get_backend(find_library=lambda x: libusb_dll_path)
    #backend = usb.backend.libusb0.get_backend(find_library=lambda x: 'D:\\Github\\Storage\\python\\udev\\U盘自动拷贝\\libusb\\amd64\\libusb0.dll')
    #print(backend)
    print(usb.backend.libusb0.get_backend())
    print(usb.backend.libusb1.get_backend())
    backend = usb.backend.libusb1.get_backend()
    
    #logger.info(list(usb.core.find(find_all=True)))
    #logger.info(get_usb_devices(backend))
    devices = list(usb.core.find(find_all=True))
    if devices:
        logger.info(len(devices))
        logger.info(type(devices[0]))
    
    for device in devices:
        #print(str(device))
        #device.set_configuration()
        pass

    vendor_id = 0x8086
    product_id = 0x7020
    
    print(usb.core.show_devices())
    dev = usb.core.find(idVendor=vendor_id, idProduct=product_id)
    if dev is None:
        raise ValueError('Device not found')
    print(dev)
    return
    
    protocol = 'USB2.0'
    busses = usb.busses()
    logger.info('type(busses): {}'.format(type(busses)))
    for bus in busses:
        #logger.info('len(bus.devices): {}'.format(len(bus.devices)))
        for dev in bus.devices:
            #logger.info('dev idVendor: {}, idProduct: {}'.format(dev.idVendor, dev.idProduct))
            if dev.idVendor == vendor_id and dev.idProduct == product_id:
                logger.info('Test vehicle %s device FOUND!' %protocol)
                logger.info('iManufacturer   : %s' %usb.util.get_string(dev.dev, 256, 1))
                logger.info('iProduct            : %s' %usb.util.get_string(dev.dev, 256, 2))
                logger.info('iSerialNumber   : %s' %usb.util.get_string(dev.dev, 256, 3))
                return dev
    logger.info('Test vehicle %s device NOT FOUND!' %protocol)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    debug()
    #main()
    #test()

    end_time = time.time()
    logger.info('process spend {} s.'.format(round(end_time - start_time, 3)))
    


