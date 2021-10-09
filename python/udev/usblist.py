# -*- coding: utf-8 -*-
"""
文 件 名: usblist.py
文件描述: 查找当前系统是否存在pvid的设备
用    法: python usblist.py 8086
作    者: HanKin
创建日期: 2021.08.16
修改日期：2021.08.16

Copyright (c) 2021 HanKin. All rights reserved.
"""

import sys
import win32com.client

def get_usb_info(usb_id):
        ids_arr = []
        wmi = win32com.client.GetObject("winmgmts:")
        for pnp in wmi.InstancesOf('Win32_PnPEntity'):
                name = pnp.Name
                id_str = pnp.DeviceID
                status = pnp.Status
                desc = pnp.Description
                

                if name == None:
                        name = ""
                if id_str == None:
                        id_str = ""
                if status == None:
                        status = ""
                if desc == None:
                        desc = ""
                ids_arr.append(name + '|' + id_str + '|' + status + "|" + desc)
                        
                if usb_id in id_str:
                        return "{\"success\":true, \"name\":\"%s\", \"id_str\":\"%s\", \"status\":\"%s\"}" %(name, id_str, status)        
	
        if usb_id=="-all":
                return ids_arr
				
        return "\"sucess\":false, \"message\":\"not find {0} in {1}\"".format(usb_id, ids_arr)

usb_id = sys.argv[1]
ret = get_usb_info(usb_id)
print(ret)
