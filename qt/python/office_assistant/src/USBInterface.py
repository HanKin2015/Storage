# -*- coding: utf-8 -*-
"""
文 件 名: USBInterface.py
文件描述: USB设备接口
备    注: pip install pyusb
作    者: HanKin
创建日期: 2023.03.20
修改日期：2023.05.26

Copyright (c) 2023 HanKin. All rights reserved.
"""

import win32com.client
from log import logger
import usb.util
import usb.backend.libusb1
import usb.backend.libusb1 as libusb1
import usb.backend.libusb0 as libusb0
import usb.backend.openusb as openusb
import time
import winreg
import platform

def get_udev_info_list():
    """获取当前所有USB设备信息列表
    https://learn.microsoft.com/zh-cn/windows/win32/cimwin32prov/win32-pnpentity
    官方已说明：Windows Server 2012 R2、Windows 8.1、Windows Server 2012、Windows 8、Windows Server 2008 R2、Windows 7、Windows Server 2008 和 Windows Vista：不支持属性Present，PNPClass。
    """
    
    logger.info('get usb device infomation list')
    
    # 创建WMI服务对象
    wmi = win32com.client.GetObject("winmgmts:")

    udev_info_list = []
    for pnp in wmi.InstancesOf('Win32_PnPEntity'):
        if 'USB\\VID' in pnp.DeviceID:
            for prop in pnp.Properties_:
                logger.debug('{} : {}'.format(prop.Name, prop.Value))
            logger.debug('')

            udev_info = dict({'Name': pnp.Name,
                                 'deviceID': pnp.deviceID,
                                 'Service': pnp.Service,
                                 'ConfigManagerErrorCode': pnp.ConfigManagerErrorCode,
                                 'Status': pnp.Status,
                                 'HardWareID': pnp.HardWareID,
                                 'SystemName': pnp.SystemName})
            if platform.system() == 'Windows':
                win_ver = platform.win32_ver()
                if win_ver[0] == '7':
                    logger.info('当前系统为Windows 7')
                    udev_info['PNPClass'] = 'USB'
                else:
                    logger.info('当前系统为Windows，但不是Windows 7')
                    udev_info['PNPClass'] = pnp.PNPClass
            else:
                logger.error('当前系统不是Windows')

            udev_info_list.append(udev_info)
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
    
    logger.info('start get usb devices({}:{}) descriptor'.format(vid, pid))
    
    # 获取USB设备
    #backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")
    #backend = my_get_backend_ex()
    #if backend == None:
    #    logger.error('libusb-1.0.dll not found, {}:{}'.format(vid, pid))
    #    return None, None
    
    udev = None
    try:
        backend = usb.backend.libusb0.get_backend()
        logger.info(backend)
        udev = usb.core.find(idVendor=int(vid, 16), idProduct=int(pid, 16))
    except Exception as err:
        logger.error(err)
        return None, None
    if udev is None:
        logger.error('device not found, {}:{}'.format(vid, pid))
        return None, None
    
    # 获取设备描述符
    desc_type = usb.util.DESC_TYPE_DEVICE
    device_desc = udev._get_full_descriptor_str()
    #device_desc = usb.util.find_descriptor(udev, bDescriptorType=desc_type)
    logger.debug(device_desc)

    # 获取配置描述符
    desc_type = usb.util.DESC_TYPE_CONFIG
    cfg_desc = usb.util.find_descriptor(udev, bDescriptorType=desc_type)
    logger.debug(cfg_desc)
    
    logger.info('get usb devices({}:{}) descriptor success'.format(vid, pid))
    return device_desc, cfg_desc

def get_bcdUSB(device_desc):
    """
    """
    
    lines = device_desc.split('\n')
    logger.debug(len(lines))
    
    for line in lines:
        if 'bcdUSB' in line:
            bcdUSB = line.split(':')
            logger.debug(bcdUSB)
            return bcdUSB[1].strip()

def get_endpoint_attributes(cfg_desc):
    """
    """
    
    transfer_types = []
    for interface_number in range(cfg_desc.bNumInterfaces):
        interface = cfg_desc[interface_number, 0]
        logger.debug(interface.bInterfaceNumber)
        logger.debug(interface.bNumEndpoints)
        if interface.bNumEndpoints:
            ep = usb.util.find_descriptor(interface)
            logger.debug(ep.bmAttributes)
            transfer_types.append(ep.bmAttributes)
        logger.debug('')
        try:
            interface = cfg_desc[interface_number, 1]
            logger.debug(interface.bInterfaceNumber)
            logger.debug(interface.bNumEndpoints)
            if interface.bNumEndpoints:
                ep = usb.util.find_descriptor(interface)
                logger.debug(ep.bmAttributes)
                transfer_types.append(ep.bmAttributes)
            logger.debug('-')
        except:
            pass
    logger.debug(transfer_types)
    transfer_types = [x & 3 for x in transfer_types]
    logger.debug(transfer_types)
    """
    USB中的端点（Endpoint）是USB设备和主机之间进行数据传输的通道。每个端点都有一个描述符（Endpoint Descriptor），其中包含了一些属性信息，其中之一就是bmAttributes。

    bmAttributes是一个8位的字段，用于描述端点的属性。它的各个位的含义如下(在usb_20.pdf中9.6.6章有介绍)：
        Bit 0-1: Transfer Type（传输类型）：0表示控制传输，1表示同步传输，2表示批量传输，3表示中断传输。
        Bit 2-3: Synchronization Type（同步类型）：仅在传输类型为同步传输时有效。0表示没有同步，1表示异步，2表示自适应，3表示同步。
        Bit 4-5: Usage Type（使用类型）：仅在传输类型为同步传输时有效。0表示数据端点，1表示反馈端点，2表示显式反馈数据端点，3保留。
        Bit 6: Reserved（保留）：必须为0。
        Bit 7: Direction（方向）：0表示输出端点（从主机到设备），1表示输入端点（从设备到主机）。
    
    因此，bmAttributes字段可以用来描述端点的传输类型、同步类型、使用类型和方向等属性。
    """
    map_model = {0: 'ctrl', 1: 'iso', 2: 'bulk', 3: 'int'}
    transfer_types = list(map(lambda x: map_model[x], transfer_types))
    transfer_types = list(set(transfer_types))
    logger.debug(transfer_types)
    return transfer_types

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
    logger.debug(type(wql))
    logger.debug(wql)
    drivers = wmi.ExecQuery(wql)
    logger.debug(type(drivers))
    logger.debug(len(drivers))
    if drivers:
        for prop in drivers[0].Properties_:
           logger.debug(prop.Name, ":", prop.Value)
        return drivers[0].InfName

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
                logger.debug(prop.Name, ":", prop.Value)

def get_sys_inf_path_name(service, hardware_id):
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
    if platform.win32_ver()[0] == '7':
        inf_names = get_inf_name(hardware_id)
    else:
        inf_names = winreg.QueryValueEx(key, 'Owners')[0]

    # 输出键值
    logger.debug(sys_path)
    logger.debug(inf_names)

    # 关闭键和注册表
    winreg.CloseKey(key)
    winreg.CloseKey(reg)
    
    return sys_path, inf_names

def get_computer_system_info():
    """
    """
    
    # 获取WMI对象
    wmi = win32com.client.GetObject('winmgmts:')

    # 查询操作系统信息
    os = wmi.ExecQuery('SELECT * FROM Win32_OperatingSystem')
    #os = wmi.ExecQuery('SELECT * FROM Win32_ComputerSystem')
    #os = wmi.ExecQuery('SELECT * FROM Win32_Processor')
    
    
    logger.debug(len(os))
    for prop in os[0].Properties_:
        logger.debug(prop.Name, ":", prop.Value)

def get_network_adapter_configuration():
    """获取ip地址行不通
    """
    
    # 获取WMI对象
    wmi = win32com.client.GetObject('winmgmts:')
    address = wmi.ExecQuery('SELECT * FROM Win32_NetworkAdapterConfiguration')
    for elem in address:
        logger.debug(elem.IPAddress, elem.ServiceName)

def get_system_info():
    """
    """
    
    # 获取WMI对象
    wmi = win32com.client.GetObject('winmgmts:')
    
    os = wmi.ExecQuery('SELECT * FROM Win32_OperatingSystem')
    cs = wmi.ExecQuery('SELECT * FROM Win32_ComputerSystem')
    
    logger.debug('os len = {}, cs len = {}'.format(len(os), len(cs)))
    return {'CSCaption': cs[0].Caption,
            'UserName': cs[0].UserName,
            'OSCaption': os[0].Caption,
            'OSArchitecture': os[0].OSArchitecture,
            'Version': os[0].Version,
            'LastBootUpTime': os[0].LastBootUpTime}

def main():
    """主函数
    """

    hex_number = 0x3505
    logger.info(string2hex('3505'))
    logger.info(hex2string(hex_number))
    
    udev_info_list = get_udev_info_list()
    get_vid_pid('USB\VID_0AC8&PID_3500&MI_02\6&197C435A&0&0002')
    device_desc, cfg_desc = get_udev_descriptor('090c', '2000')
    
    #get_inf_name(udev_info_list[4]['HardWareID'][0])
    #get_sys_path(udev_info_list[4]['Service'])
    #get_sys_inf_path_name(udev_info_list[2]['Service'], udev_info_list[2]['HardWareID'][0])
    
    #get_computer_system_info()
    #get_network_adapter_configuration()
    #system_info = get_system_info()
    #for key, value in system_info.items():
     #   logger.info('{}: {}'.format(key, value))

    bcdUSB = get_bcdUSB(device_desc)
    logger.debug(bcdUSB)
    get_endpoint_attributes(cfg_desc)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))