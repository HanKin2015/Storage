# -*- coding: utf-8 -*-
"""
文 件 名: write_data_to_udev.py
文件描述: 向usb设备写数据
备    注: 失败，超时，可能是中间接了一个hub
作    者: HanKin
创建日期: 2022.08.02
修改日期：2022.08.02

Copyright (c) 2022 HanKin. All rights reserved.
"""

import usb.core
import usb.util
import os
import usb.backend.libusb0
import usb.backend.libusb1

libusb0_dll_path = os.getcwd()+'/libusb0.dll'
libusb1_dll_path = os.getcwd()+'/libusb-1.0.dll'
print('libusb0_dll_path: {}'.format(libusb0_dll_path))
print('libusb1_dll_path: {}'.format(libusb1_dll_path))

if not os.path.exists(libusb0_dll_path):
    print('libusb0.dll file not exists')
if not os.path.exists(libusb1_dll_path):
    print('libusb-1.0.dll file not exists')

#backend = usb.backend.libusb0.get_backend(find_library=lambda x: libusb0_dll_path)
backend = usb.backend.libusb1.get_backend(find_library=lambda x: libusb1_dll_path)

dev =  usb.core.find(idVendor= 0x30de, idProduct= 0x6545)
if dev is None:
    raise ValueError('Device not found')
print(dev)
# set the active configuration. With no arguments, the first
# configuration will be the active one
dev.set_configuration()

# get an endpoint instance
cfg = dev.get_active_configuration()
intf = cfg[(0,0)]

ep = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT)
print('23---', ep)
assert ep is not None

# write the data
#ep.write('test')
dev.write(0x81, 'test')