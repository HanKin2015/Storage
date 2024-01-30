# -*- coding: utf-8 -*-
"""
文 件 名: get_udev_driver_detail.py
文件描述: 获取摄像头设备加载的驱动程序详细信息
备    注: 通过注册表和inf文件获取
作    者: HanKin
创建日期: 2024.01.30
修改日期：2024.01.30

Copyright (c) 2024 HanKin. All rights reserved.
"""
import win32com.client
import configparser
import winreg
import os
import chardet

def test():
    wmi = win32com.client.GetObject('winmgmts:')
    pnps = wmi.ExecQuery("Select * From Win32_PnPEntity WHERE ClassGuid='{36FC9E60-C465-11CF-8056-444553540000}'")
    for pnp in pnps:
        for prop in pnp.Properties_:
            print('{:27} : {}'.format(prop.Name, prop.Value))
        print('')

def detect_encoding(file_path):
    with open(file_path, 'rb') as f:
        rawdata = f.read()
    result = chardet.detect(rawdata)
    print(result['encoding'])
    return result['encoding']
    
def get_camera_list():
    """使用Win32_PnPSignedDriver获取设备信息似乎有点慢，没有Win32_PnPEntity获取来的快inf_path
    """
    camera_list = []
    wmi = win32com.client.GetObject("winmgmts:")
    wql = "Select * From Win32_PnPSignedDriver WHERE DeviceID LIKE '%%USB\\\\VID%%'"
    for pnp in wmi.ExecQuery(wql):
        if pnp.DeviceClass == "CAMERA":
            camera = dict({'ClassGuid': pnp.ClassGuid,
                           'DeviceID': pnp.DeviceID,
                           'DeviceClass': pnp.DeviceClass,
                           'DriverName': pnp.DriverName,
                           'DriverProviderName': pnp.DriverProviderName,
                           'HardWareID': pnp.HardWareID,
                           'InfName': pnp.InfName,
                           'PDO': pnp.PDO})
            camera_list.append(camera)
        
    for camera in camera_list:
        for key, value in camera.items():
            print('{:27}: {}'.format(key, value))
        print('')
    return camera_list

def get_camera_list2():
    """使用Win32_PnPEntity获取设备信息
    """
    camera_list = []
    wmi = win32com.client.GetObject("winmgmts:")
    wql = "Select * From Win32_PnPEntity WHERE DeviceID LIKE '%%USB\\\\VID%%'"
    for pnp in wmi.ExecQuery(wql):
        if pnp.PNPClass == "Camera":
            camera = dict({'ClassGuid': pnp.ClassGuid,
                           'DeviceID': pnp.DeviceID,
                           'PNPClass': pnp.PNPClass,
                           'Manufacturer': pnp.Manufacturer,
                           'Description': pnp.Description,
                           'SystemName': pnp.SystemName,
                           'Service': pnp.Service,
                           'Status': pnp.Status})
            camera_list.append(camera)
        
    for camera in camera_list:
        for key, value in camera.items():
            print('{:27}: {}'.format(key, value))
        print('')
    return camera_list

def get_driver_detail_by_inf(inf_path):
    """通过inf文件读取SourceDisksFiles字段
    """
    config_parser = configparser.ConfigParser(allow_no_value=True, strict=False)
    encoding = detect_encoding(inf_path)
    config_parser.read(inf_path, encoding=encoding)
    driver_detail_list = []
    if config_parser.has_section('SourceDisksFiles'):
        value = config_parser.items('SourceDisksFiles')
        print('inf文件读取到的值：', value)
        driver_detail_list = [item[0] for item in value]
    return driver_detail_list

def regedit_interface(registry, reg_path, item):
    """
    注册表操作接口
    :param registry: 注册表根路径
    :param reg_path: 注册表路径
    :param item: 注册表项
    :return str: 注册表项的值
    """
    # 打开注册表
    reg = winreg.ConnectRegistry(None, registry)
    key = None
    value = None
    try:
        # 打开指定路径下的键
        key = winreg.OpenKey(reg, reg_path)
        # 读取键值
        value = winreg.QueryValueEx(key, item)
        # 输出键值
        print(value)
    except Exception as error:
        print('{} -> {}: {}'.format(reg_path, item, error))

    # 关闭键和注册表
    if key:
        winreg.CloseKey(key)
    winreg.CloseKey(reg)
    return value

def get_filter_driver_list(reg_path):
    """获取过滤驱动列表
    """
    driver_detail_list = []
    
    registry = winreg.HKEY_LOCAL_MACHINE
    
    item     = "LowerFilters"
    value    = regedit_interface(registry, reg_path, item)
    if value:
        driver_list = value[0]
        driver_detail_list.extend(driver_list)
    
    item     = "UpperFilters"
    value    = regedit_interface(registry, reg_path, item)
    if value:
        driver_list = value[0]
        driver_detail_list.extend(driver_list)
    
    print(driver_detail_list)
    return driver_detail_list

def get_driver_detail_by_classguid(class_guid):
    """过滤驱动
    """
    reg_path = r"SYSTEM\CurrentControlSet\Control\Class\{}".format(class_guid)
    return get_filter_driver_list(reg_path)
        
def get_driver_detail_by_deviceid(device_id):
    """过滤驱动
    """
    reg_path = r"SYSTEM\CurrentControlSet\Enum\{}".format(device_id)
    return get_filter_driver_list(reg_path)

def get_vid_pid_by_deviceid(device_id):
    """从设备的deviceID获取vid和pid
    """
    vid = device_id[8:12]
    pid = device_id[17:21]
    vid_pid = "{}:{}".format(vid, pid)
    print(vid_pid)
    return vid_pid

def get_udev_driver_detail_by_entity():
    """
    """
    camera_list = get_camera_list2()
    for camera in camera_list:
        driver_detail_list = []
        
        Service = camera.get("Service", "")
        reg_path = r"SYSTEM\CurrentControlSet\Services\{}".format(Service)
        registry = winreg.HKEY_LOCAL_MACHINE
        item     = "Owners"
        value    = regedit_interface(registry, reg_path, item)
        
        if value:
            for inf_name in value[0]:
                inf_path = r"C:\Windows\INF\{}".format(inf_name)
                if os.path.exists(inf_path):
                    driver_detail_list.extend(get_driver_detail_by_inf(inf_path))
        driver_detail_list.extend(get_driver_detail_by_classguid(camera.get("ClassGuid", "")))
        driver_detail_list.extend(get_driver_detail_by_deviceid(camera.get("DeviceID", "")))
        
        vid_pid = get_vid_pid_by_deviceid(camera.get("DeviceID", ""))
        #driver_detail_list = set(driver_detail_list)
        print("{} = {}".format(vid_pid, driver_detail_list))

def get_udev_driver_detail_by_signed():
    """缺点还是很明显，无法快速及时的检测出变化，摈弃
    """
    camera_list = get_camera_list()
    for camera in camera_list:
        driver_detail_list = []
        
        inf_name = camera.get("InfName", "")
        inf_path = r"C:\Windows\INF\{}".format(inf_name)
        driver_detail_list.extend(get_driver_detail_by_inf(inf_path))
        driver_detail_list.extend(get_driver_detail_by_classguid(camera.get("ClassGuid", "")))
        driver_detail_list.extend(get_driver_detail_by_deviceid(camera.get("DeviceID", "")))
        
        vid_pid = get_vid_pid_by_deviceid(camera.get("DeviceID", ""))
        #driver_detail_list = set(driver_detail_list)
        print("{} = {}".format(vid_pid, driver_detail_list))

if __name__ == '__main__':
    get_udev_driver_detail_by_entity()
    #get_udev_driver_detail_by_signed()
    os.system("pause")