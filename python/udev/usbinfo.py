"""
文 件 名: usbinfo.py
文件描述: 查找当前系统存在的设备
用    法: python usbinfo.py
作    者: HanKin
创建日期: 2021.08.16
修改日期：2021.08.16

Copyright (c) 2021 HanKin. All rights reserved.
"""

import win32com.client

wmi = win32com.client.GetObject("winmgmts:")
print(wmi)
for pnp in wmi.InstancesOf('Win32_PnPEntity'):
        print(pnp.Name)
        print(pnp.DeviceID)
        print(pnp.Status)

print("===================win32_usbcontrollerdevice=================")       
for usb in wmi.InstancesOf("win32_usbcontrollerdevice"):
	print(usb.Dependent)
	print(usb.AccessState)
	print(usb.Antecedent)
	print(usb.NegotiatedSpeed)
	
print("===================win32_usbcontroller=================")
for usb in wmi.InstancesOf("win32_usbcontroller"):
	print(usb.Name)
	print(usb.DeviceID)
	print(usb.Status)
	print(usb.StatusInfo)
	print(usb.Description)