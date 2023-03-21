# -*- coding: utf-8 -*-
"""
文 件 名: pyshark_get_keyborad.py
文件描述: windows的话需要修改代码，安装了wireshark后就会有tshark.exe程序，后面再验证该代码
作    者: HanKin
创建日期: 2022.10.20
修改日期：2022.10.20

Copyright (c) 2022 HanKin. All rights reserved.
"""

import pyshark
# Get keystrokes data
print("\n----- Capturing keystrokes from usbmon0 --------------------")
capture = pyshark.LiveCapture(interface='usbmon0', output_file='output.pcap')

# Source: https://www.programcreek.com/python/example/92561/pyshark.LiveCapture 
for i, packet in enumerate(capture.sniff_continuously()):
    try:
        data= packet[1].usb_capdata.split(":")
        print(data)
    except:
        pass
capture.clear()
capture.close()
print(f'DONE')