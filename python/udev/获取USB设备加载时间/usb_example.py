# -*- coding: utf-8 -*-
"""
文 件 名: usb_example.py
文件描述: usb.busses()无法获取成功
备    注: 未解决
作    者: HanKin
创建日期: 2022.08.02
修改日期：2022.08.02

Copyright (c) 2022 HanKin. All rights reserved.
"""

import usb
import os
import usb.backend.libusb0
import usb.backend.libusb1

#help(usb.core) 

libusb0_dll_path = os.getcwd()+'/libusb0.dll'
libusb1_dll_path = os.getcwd()+'/libusb-1.0.dll'
print('libusb0_dll_path: {}'.format(libusb0_dll_path))
print('libusb1_dll_path: {}'.format(libusb1_dll_path))

if not os.path.exists(libusb0_dll_path):
    print('libusb0.dll file not exists')
if not os.path.exists(libusb1_dll_path):
    print('libusb-1.0.dll file not exists')

backend = usb.backend.libusb0.get_backend(find_library=lambda x: libusb0_dll_path)
#backend = usb.backend.libusb1.get_backend(find_library=lambda x: libusb_dll_path)

busses = usb.busses()
for bus in busses:
    devices = bus.devices
    for device in devices:
        print(device)
        print('hello usb')