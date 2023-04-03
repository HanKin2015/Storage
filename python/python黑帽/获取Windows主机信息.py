# -*- coding: utf-8 -*-
"""
文 件 名: 获取windows主机信息.py
文件描述: 通过wmi库
作    者: HanKin
创建日期: 2023.03.31
修改日期：2023.03.31

Copyright (c) 2023 HanKin. All rights reserved.
"""

import wmi
import os
import socket
import platform

w = wmi.WMI()

#获取电脑使用者信息
for CS in w.Win32_ComputerSystem():
    #print(CS)
    print("电脑名称: %s" %CS.Caption)
    print("使用者: %s" %CS.UserName)
    print("制造商: %s" %CS.Manufacturer)
    if platform.win32_ver()[0] != '7':
        print("系统信息: %s" %CS.SystemFamily)
    print("工作组: %s" %CS.Workgroup)
    print("机器型号: %s" %CS.model)
    print("")

#获取操作系统信息
for OS in w.Win32_OperatingSystem():
    #print(OS)
    print("操作系统: %s" %OS.Caption)
    print("语言版本: %s" %OS.MUILanguages)
    print("系统位数: %s" %OS.OSArchitecture)
    print("注册人: %s" %OS.RegisteredUser)
    print("系统驱动: %s" %OS.SystemDevice)
    print("系统目录: %s" %OS.SystemDirectory)
    print("")

#获取电脑IP和MAC信息（这种方法不方便，需要先知道服务名）
#for address in w.Win32_NetworkAdapterConfiguration(ServiceName = "netkvm"):
for address in w.Win32_NetworkAdapterConfiguration():
    if address.IPAddress is not None:
        print(address.ServiceName, address.IPAddress)
        #print(address)
        print("IP地址: ", address.IPAddress)
        print("MAC地址: %s" % address.MACAddress)
        print("网络描述: %s" % address.Description)
        print("")

#获取电脑CPU信息
for processor in w.Win32_Processor():
    #print(processor)
    print("CPU型号: %s" % processor.Name.strip())
    print("CPU核数: %s" % processor.NumberOfCores)
    print("")

#获取BIOS信息
for BIOS in w.Win32_BIOS():
    #print(BIOS)
    print("使用日期: %s" %BIOS.Description)
    print("主板型号: %s" %BIOS.SerialNumber)
    print("当前语言: %s" %BIOS.CurrentLanguage)
    print("")

#获取内存信息
for memModule in w.Win32_PhysicalMemory():
    totalMemSize = int(memModule.Capacity)
    print("内存厂商: %s" %memModule.Manufacturer)
    print("内存型号: %s" %memModule.PartNumber)
    print("内存大小: %.2fGB" %(totalMemSize/1024**3))
    print("")

#获取磁盘信息
for disk in w.Win32_DiskDrive():
    diskSize = int(disk.size)
    print("磁盘名称: %s" %disk.Caption)
    print("硬盘型号: %s" %disk.Model)
    print("磁盘大小: %.2fGB" %(diskSize/1024**3))

#获取显卡信息
for xk in w.Win32_VideoController():
    print("显卡名称: %s" %xk.name)
    print("")
       
#获取计算机名称和IP（不准确）
hostname = socket.gethostname()
ip = socket.gethostbyname(hostname)
print("计算机名称: %s" %hostname)
print("IP地址: %s" %ip)
print("")


import win32com.client
def get_ip_mac():
    """获取ip地址行不通
    """
    
    # 获取WMI对象
    wmi = win32com.client.GetObject('winmgmts:')
    address = wmi.ExecQuery('SELECT * FROM Win32_NetworkAdapterConfiguration')
    for elem in address:
        if elem.IPAddress and elem.DefaultIPGateway:    # 真实的IP地址存在默认网关
            print(elem.IPAddress, elem.ServiceName)
            print(type(elem.IPAddress))
            print(len(elem.IPAddress))  # 可能存在第二个成员是本地链接IPv6地址
            return elem.IPAddress[0], elem.MACAddress
            #for prop in elem.Properties_:
            #    print(prop.Name, ":", prop.Value)

ip, mac = get_ip_mac()
print(ip)
print(mac)
