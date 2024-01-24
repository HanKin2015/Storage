# -*- coding: utf-8 -*-
"""
文 件 名: winreg_example.py
文件描述: 注册表操作
参    考: 
作    者: HanKin
创建日期: 2024.01.19
修改日期：2024.01.19

Copyright (c) 2024 HanKin. All rights reserved.
"""
import winreg
import os

def regedit_interface(registry, reg_path, item):
    """
    注册表操作接口
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
        print('{}\{}, {}'.format(key, value, error))

    # 关闭键和注册表
    if key:
        winreg.CloseKey(key)
    winreg.CloseKey(reg)
    return value

def is_exist_friendly_business():
    """
    检查USB设备是否加载xx驱动
    """
    reg_path = r"SYSTEM\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}"
    item     = "LowerFilters"
    registry = winreg.HKEY_LOCAL_MACHINE
    value    = regedit_interface(registry, reg_path, item)
    print(value)
    driver_list = value[0]
    if "vdi_usb_hub_filter" in driver_list:
        print("yes")

    # 检查文件驱动文件是否存在
    if os.path.exists(r"C:\Windows\System32\drivers\vdiusbfilter.sys"):
        print("yes")

is_exist_friendly_business()