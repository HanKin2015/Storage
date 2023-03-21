# -*- coding: utf-8 -*-
"""
文 件 名: USBInterface.py
文件描述: USB设备接口
作    者: HanKin
创建日期: 2023.03.20
修改日期：2023.03.20

Copyright (c) 2023 HanKin. All rights reserved.
"""

import win32com.client
from log import logger
import usb.util
import usb.backend.libusb1
import time
import winreg

def get_udev_info_list():
    """获取当前所有USB设备信息列表
    """
    
    # 创建WMI服务对象
    wmi = win32com.client.GetObject("winmgmts:")

    udev_info_list = []
    for pnp in wmi.InstancesOf('Win32_PnPEntity'):
        if 'USB\\VID' in pnp.DeviceID:
            udev_info_list.append({'pnp.Name': pnp.Name,
                                 'pnp.deviceID': pnp.deviceID,
                                 'pnp.PNPClass': pnp.PNPClass,
                                 'pnp.Service': pnp.Service,
                                 'pnp.ConfigManagerErrorCode': pnp.ConfigManagerErrorCode,
                                 'pnp.Status': pnp.Status,
                                 'pnp.HardWareID': pnp.HardWareID,
                                 'pnp.SystemName': pnp.SystemName})
    for udev_info in udev_info_list:
        for key, value in udev_info.items():
            logger.debug('{}: {}'.format(key, value))
        logger.debug('')
    
    return udev_info_list
    
def get_vid_pid(device_id):
    """从设备的deviceID获取vid和pid
    """
    
    vid = device_id[8:12]
    pid = device_id[17:21]
    logger.debug('{}:{}'.format(vid, pid))
    return vid, pid

def hex2string(hex_number):
    """十六进制数转字符串
    """
    
    return str(hex_number)
    
def string2hex(hex_string):
    """字符串转十六进制数
    """
    
    return int(hex_string, 16)
    
def get_udev_descriptor(vid, pid):
    """获取USB设备描述符
    """
    
    # 获取USB设备
    backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")
    udev = usb.core.find(idVendor=int(vid, 16), idProduct=int(pid, 16), backend=backend)
    if udev is None:
        raise ValueError('Device not found')
    
    # 获取设备描述符
    desc_type = usb.util.DESC_TYPE_DEVICE
    device_desc = udev._get_full_descriptor_str() 
    #logger.debug(device_desc)

    # 获取配置描述符
    desc_type = usb.util.DESC_TYPE_CONFIG
    cfg_desc = usb.util.find_descriptor(udev, bDescriptorType=desc_type)
    #logger.debug(cfg_desc)
    
    return device_desc, cfg_desc

def get_inf_name(hardware_id):
    """
    """

    # 创建WMI服务对象
    wmi = win32com.client.GetObject("winmgmts:")
    
    # 取消转义
    hardware_id = hardware_id.encode('unicode_escape').decode()
    logger.debug('HardWareID = {}'.format(hardware_id))
    
    # 获取设备驱动信息
    wql = "SELECT * FROM Win32_PnPSignedDriver WHERE HardWareID='" + hardware_id + "'"
    print(type(wql))
    print(wql)
    drivers = wmi.ExecQuery(wql)
    print(type(drivers))
    print(len(drivers))
    if drivers:
        for prop in drivers[0].Properties_:
           print(prop.Name, ":", prop.Value)

def get_sys_path(service):
    """
    """
    
    # 创建WMI服务对象
    wmi = win32com.client.GetObject("winmgmts:")
    
    # 枚举Win32_SystemDriver类中的所有设备驱动程序
    system_drivers = wmi.ExecQuery("SELECT * FROM Win32_SystemDriver")
    
    # 遍历所有设备驱动程序，获取驱动文件路径
    for system_driver in system_drivers:
        if system_driver.Name == service:
            for prop in system_driver.Properties_:
                print(prop.Name, ":", prop.Value)

def get_sys_inf_path_name(service):
    """
    """
    
    logger.debug(service)
    
    # 打开注册表
    reg = winreg.ConnectRegistry(None, winreg.HKEY_LOCAL_MACHINE)

    # 打开指定路径下的键
    key_path = r'SYSTEM\CurrentControlSet\Services\{}'.format(service)
    key = winreg.OpenKey(reg, key_path)

    # 读取键值
    sys_path = winreg.QueryValueEx(key, 'ImagePath')[0]
    inf_names = winreg.QueryValueEx(key, 'Owners')[0]

    # 输出键值
    logger.debug(sys_path)
    logger.info(inf_names)

    # 关闭键和注册表
    winreg.CloseKey(key)
    winreg.CloseKey(reg)
    
    return sys_path, inf_names

def main():
    """主函数
    """

    hex_number = 0x3505
    logger.info(string2hex('3505'))
    logger.info(hex2string(hex_number))
    
    udev_info_list = get_udev_info_list()
    get_vid_pid('USB\VID_0AC8&PID_3500&MI_02\6&197C435A&0&0002')
    get_udev_descriptor('0AC8', '3500')
    
    #get_inf_name(udev_info_list[4]['pnp.HardWareID'][0])
    #get_sys_path(udev_info_list[4]['pnp.Service'])
    get_sys_inf_path_name(udev_info_list[2]['pnp.Service'])

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))