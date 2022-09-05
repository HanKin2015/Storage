# -*- coding: utf-8 -*-
"""
文 件 名: wmi_example.py
文件描述: 学习wmi库
作    者: HanKin
创建日期: 2022.09.03
修改日期：2022.09.03

Copyright (c) 2022 HanKin. All rights reserved.
"""

import wmi
import time
import win32com
import pywintypes

def operate_wmi_by_wmi():
    """
    使用wmi库操作WMI
    """
    
    c = wmi.WMI()
    # 遍历进程
    for process in c.Win32_Process():
        print(process.ProcessId, process.Name)
    # 遍历服务
    for service in c.Win32_Service():
        print(service.ProcessId, service.Name)

def operate_wmi_by_win32com():
    """
    使用win32com库操作WMI
    """
    
    wmi = win32com.client.GetObject('winmgmts:/root/cimv2')
    #wmi = win32com.client.GetObject('winmgmts:') # 更简单的写法
    
    processes = wmi.InstancesOf('Win32_Process')
    for process in processes:
        print(process.ProcessID, process.Name)
        
    services = wmi.ExecQuery('Select * from Win32_Service')
    for service in services:
        print(service.ProcessID, service.Name)

def get_wmi_namespace(name):
    """
    想要了解的内容在哪个名称空间，我们应该获取哪个实例，又该获取实例中的哪些属性
    获得当前计算机上的名称空间
    """
    
    try:
        wmi = win32com.client.GetObject('winmgmts:/' + name)
        namespaces = wmi.InstancesOf('__Namespace')
        for namespace in namespaces:
            get_wmi_namespace('{name}/{subname}'.format(name=name, subname=namespace.Name))
    except pywintypes.com_error:
        print(name, 'limit of authority')
    else:
        print(name)

def test():
    """
    实战，以IIS为例
    命名空间不对，运行不了
    """
    
    wmi = win32com.client.GetObject('winmgmts:/root/microsoftiisv2')

    # 版本
    webinfo = wmi.execquery('select * from IIsWebInfo ')[0]
    version = '{major}.{min}'.format(major=webinfo.MajorIIsVersionNumber, min=webinfo.MinorIIsVersionNumber)
    print(version)

    # 站点名称
    websettings = wmi.execquery('select * from IIsWebServerSetting ')
    websites = ' | '.join(setting.ServerComment for setting in websettings)
    print(websites)

def main(): 
    #operate_wmi_by_wmi()
    #operate_wmi_by_win32com()
    #get_wmi_namespace('root')
    test()

def debug():
    main()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    #main()
    debug()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
