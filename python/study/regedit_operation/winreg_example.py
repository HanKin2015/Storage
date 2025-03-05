# -*- coding: utf-8 -*-
"""
文 件 名: winreg_example.py
文件描述: 注册表操作
注册表项常见的类型:
winreg.REG_SZ：字符串类型
winreg.REG_DWORD：32 位整数
winreg.REG_QWORD：64 位整数
winreg.REG_BINARY：二进制数据
winreg.REG_MULTI_SZ：多字符串（字符串数组）
winreg.REG_EXPAND_SZ：扩展字符串
作    者: HanKin
创建日期: 2024.01.19
修改日期：2025.03.04

Copyright (c) 2025 HanKin. All rights reserved.
"""
import winreg
import os

def regedit_interface_(registry, reg_path, item):
    """
    注册表操作接口
    :param registry: 注册表根路径
    :param reg_path: 注册表路径
    :param item: 注册表项
    :return str: 注册表项的值
    """
    print(reg_path)

    value = None
    try:
        with winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, reg_path) as key:
            # 查询注册表项的值
            value, reg_type = winreg.QueryValueEx(key, item)
            
            # 输出结果
            print("值:", value)
            print("类型:", reg_type)
    except FileNotFoundError:
        print("注册表项未找到")
    except Exception as e:
        print("发生错误:", e)
    return value

def regedit_interface(registry, reg_path, item):
    """
    注册表操作接口
    :param registry: 注册表根路径
    :param reg_path: 注册表路径
    :param item: 注册表项
    :return str: 注册表项的值
    """
    print(reg_path)

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
    检查USB设备是否加载华三驱动
    """
    reg_path = r"SYSTEM\CurrentControlSet\Control\Class\{36fc9e60-c465-11cf-8056-444553540000}"
    item     = "LowerFilters"
    registry = winreg.HKEY_LOCAL_MACHINE
    value    = regedit_interface(registry, reg_path, item)
    print(value)
    print(regedit_interface_(registry, reg_path, item))
    if value:
        driver_list = value[0]
        if "vdi_usb_hub_filter" in driver_list:
            print("yes")

    # 检查文件驱动文件是否存在
    if os.path.exists(r"C:\Windows\System32\drivers\vdiusbfilter.sys"):
        print("yes")

is_exist_friendly_business()