# -*- coding: utf-8 -*-
"""
文 件 名: hack_interface.py
文件描述: 接口
作    者: HanKin
创建日期: 2023.03.31
修改日期：2023.04.03

Copyright (c) 2023 HanKin. All rights reserved.
"""

import win32com.client
from log import logger
import time
import winreg
import platform
import base64

def regedit(registry, b64_key_path, value):
    """打开注册表获取
    """
    
    key_path = base64.b64decode(b64_key_path).decode()
    logger.debug('{}\{}'.format(key_path, value))
    
    # 打开注册表
    reg = winreg.ConnectRegistry(None, registry)

    key = None
    key_value = None
    try:
        # 打开指定路径下的键
        key = winreg.OpenKey(reg, key_path)

        # 读取键值
        key_value = winreg.QueryValueEx(key, value)

        # 输出键值
        logger.info(key_value)
    except Exception as error:
        logger.error('{}\{}, {}'.format(key_path, value, error))

    # 关闭键和注册表
    if key:
        winreg.CloseKey(key)
    winreg.CloseKey(reg)
    
    return key_value

def base64_example():
    """Base64编码例子
    base64编码是将二进制字节流编码为可打印的64个字符
    以6位分割 bit位都是0，base64约定以‘=’代替
    z -> b'eg=='
    """
    
    name = "王大锤"

    # 编码： 字符串 -> 二进制 -> base64编码
    b64_name = base64.b64encode(name.encode())
    print(b64_name)
    # b'546L5aSn6ZSk'

    # 解码：base64编码 -> 二进制 -> 字符串
    print(base64.b64decode(b64_name).decode())
    # 王大锤

def get_client_version():
    """获取客户端版本
    
    """
    
    registry     = winreg.HKEY_LOCAL_MACHINE
    b64_key_path = b'U09GVFdBUkVcV09XNjQzMk5vZGVcU2FuZ2ZvclxWREk='
    value        = 'Version'
    return regedit(registry, b64_key_path, value)

def get_vdc_version():
    """
    """

    registry     = winreg.HKEY_LOCAL_MACHINE
    b64_key_path = b'U09GVFdBUkVcV09XNjQzMk5vZGVcU2FuZ2ZvclxTU0xcVkRJ'
    value        = 'VdcVersion'
    return regedit(registry, b64_key_path, value)

def get_agent_version():
    """
    """
    
    registry     = winreg.HKEY_LOCAL_MACHINE
    b64_key_path = b'U09GVFdBUkVcV09XNjQzMk5vZGVcU2FuZ2ZvclxTU0xcVkRJ'
    value        = 'Version'
    return regedit(registry, b64_key_path, value)

def get_usb_lower_filters():
    """
    """
    
    registry     = winreg.HKEY_LOCAL_MACHINE
    b64_key_path = b'U1lTVEVNXEN1cnJlbnRDb250cm9sU2V0XENvbnRyb2xcQ2xhc3NcezM2ZmM5ZTYwLWM0NjUtMTFjZi04MDU2LTQ0NDU1MzU0MDAwMH0='
    value        = 'LowerFilters'
    return regedit(registry, b64_key_path, value)

def get_image_lower_filters():
    """
    """
    
    registry     = winreg.HKEY_LOCAL_MACHINE
    b64_key_path = b'U1lTVEVNXEN1cnJlbnRDb250cm9sU2V0XENvbnRyb2xcQ2xhc3NcezZiZGQxZmM2LTgxMGYtMTFkMC1iZWM3LTA4MDAyYmUyMDkyZn0='
    value        = 'LowerFilters'
    return regedit(registry, b64_key_path, value)

def get_camera_lower_filters():
    """
    """
    
    registry     = winreg.HKEY_LOCAL_MACHINE
    b64_key_path = b'U1lTVEVNXEN1cnJlbnRDb250cm9sU2V0XENvbnRyb2xcQ2xhc3Nce2NhM2U3YWI5LWI0YzMtNGFlNi04MjUxLTU3OWVmOTMzODkwZn0='
    value        = 'LowerFilters'
    return regedit(registry, b64_key_path, value)

def get_computer_system_info():
    """
    """
    
    # 获取WMI对象
    wmi = win32com.client.GetObject('winmgmts:')

    # 查询操作系统信息
    os = wmi.ExecQuery('SELECT * FROM Win32_OperatingSystem')
    #os = wmi.ExecQuery('SELECT * FROM Win32_ComputerSystem')
    #os = wmi.ExecQuery('SELECT * FROM Win32_Processor')
    
    
    print(len(os))
    for prop in os[0].Properties_:
        print(prop.Name, ":", prop.Value)

def main():
    """主函数
    """

    get_client_version()
    get_vdc_version()
    get_agent_version()
    get_usb_lower_filters()
    get_image_lower_filters()
    get_camera_lower_filters()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))