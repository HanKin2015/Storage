# -*- coding: utf-8 -*-
"""
文 件 名: parse_descriptor.py
文件描述: 解析usb描述符信息
作    者: HanKin
备    注: 
创建日期: 2025.01.20
修改日期：2025.01.20

Copyright (c) 2025 HanKin. All rights reserved.
"""
import json

with open("device_info.json", "r") as f:
    device_infos = json.load(f)

device_list = device_infos.get("device_list", "")
for index, device_desc in enumerate(device_list):
    # 枚举设备描述符
    if isinstance(device_desc, dict):
        vid_pid = "{:04x}:{:04x}".format(int(device_desc.get("idVendor"), 16),
                                                 int(device_desc.get("idProduct"), 16))
        print("current parse device info vid_pid {}".format(vid_pid))
        configurations_num = int(device_desc.get("bNumConfigurations"))
        for i in range(configurations_num):
            config_desc = device_list[index + 1][i * 2]
            interface_list = device_list[index + 1][i * 2 + 1]
            for j in range(int(config_desc.get("bNumInterfaces"))):
                interface_desc = interface_list[j * 2]
                # 枚举端口描述符
                endpoint_num = int(interface_desc.get("bNumEndpoints"))
                endpoint_list = device_list[index + 1][i * 2 + 1][j * 2 + 1]
                for k in range(endpoint_num):
                    endpoint_desc = endpoint_list[k]
                    print(int(endpoint_desc.get("bmAttributes", 0)))

"""
(base) D:\Github\Storage\python\study\container\json>python parse_descriptor.py
current parse device info vid_pid 17ef:608c
3
3
current parse device info vid_pid 17ef:608d
3
current parse device info vid_pid 18d1:d001
2
2
current parse device info vid_pid 0403:6001
2
2
current parse device info vid_pid 05e3:0749
2
2
"""