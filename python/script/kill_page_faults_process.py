# -*- coding: utf-8 -*-
"""
文 件 名: kill_page_faults_process.py
文件描述: 获取设备管理器中页面错误
作    者: HanKin
创建日期: 2023.07.17
修改日期：2023.07.17

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
import stat
import time
import win32com.client
import psutil
import ctypes

def enmu_programs_by_wmi():
    """比较费时
    """
    
    # 创建WMI对象
    wmi = win32com.client.GetObject("winmgmts:")

    # 查询所有已安装的程序
    programs = wmi.ExecQuery("SELECT * FROM Win32_Product")

    # 遍历所有程序，获取名称和版本号
    for program in programs:
        print("程序名称：", program.Name)
        print("版本号：", program.Version)

def enmu_programs_by_winreg():
    import winreg

    # 打开注册表键
    key = winreg.OpenKey(winreg.HKEY_LOCAL_MACHINE, r"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall")

    # 遍历所有子键
    for i in range(winreg.QueryInfoKey(key)[0]):
        try:
            # 获取子键名称和值
            subkey_name = winreg.EnumKey(key, i)
            subkey = winreg.OpenKey(key, subkey_name)
            name = winreg.QueryValueEx(subkey, "DisplayName")[0]
            version = winreg.QueryValueEx(subkey, "DisplayVersion")[0]

            # 判断是否为已安装的程序
            if name and version:
                print("程序名称：", name)
                print("版本号：", version)
                print()
        except OSError:
            continue

def enmu_programs_by_winreg():
    """
    """
    
    # 遍历所有进程
    for proc in psutil.process_iter(['name', 'exe', 'cmdline']):
        try:
            # 获取进程启动命令
            cmdline = ' '.join(proc.cmdline())
        except (psutil.AccessDenied, psutil.ZombieProcess):
            continue
        except psutil.NoSuchProcess:
            continue

        # 判断进程是否为已安装的程序
        if 'mintty.exe' in cmdline and '/x{' in cmdline:
            # 获取程序名称和版本号
            name = cmdline.split('/x{')[0].split('\\')[-1].strip()
            version = cmdline.split('/x{')[1].split('}')[0].strip()

            # 获取进程ID
            pid = proc.pid

            print("程序名称：", name)
            print("版本号：", version)
            print("进程ID：", pid)
            print("启动命令：", cmdline)
            print()
        
        if 'mintty.exe' in cmdline:
            print(cmdline)

def is_admin():
    try:
        return ctypes.windll.shell32.IsUserAnAdmin()
    except:
        return False

if __name__ == '__main__':
    """程序入口
    """

    if is_admin():
        print("当前程序以管理员权限运行")
    else:
        print("当前程序未以管理员权限运行")

    # 获取所有进程的信息
    processes = psutil.process_iter()
    
    # 创建一个字典，用于存储进程ID和页面错误数量
    page_faults_dict = {}
    
    # 忽略的进程
    ignore_processes = ['svchost.exe', 'chrome.exe', 'explorer.exe', 'Code.exe', 'wps.exe', 'devenv.exe']

    # 遍历所有进程，获取页面错误数量
    for process in processes:
        try:
            if process.name() == 'aTrustAgent.exe':
                print(process)
                #process.kill()
        
            # 获取进程的内存信息
            mem_info = process.memory_info()
            # 获取页面错误数量
            page_faults = mem_info.num_page_faults
            # 将进程ID和页面错误数量存储到字典中
            page_faults_dict[process.pid] = page_faults
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess) as err:
            # 如果进程不存在、权限不足或者是僵尸进程，则忽略该进程
            print(err)
            pass

    # 对字典按照页面错误数量进行排序
    sorted_page_faults = sorted(page_faults_dict.items(), key=lambda x: x[1], reverse=True)

    # 输出前十个页面错误数量最高的进程
    kill_count = 0
    for i in range(20):
        if i >= len(sorted_page_faults):
            break
        pid = sorted_page_faults[i][0]
        page_faults = sorted_page_faults[i][1]
        #print("进程ID：{}，页面错误数量：{}".format(pid, page_faults))
        # 杀掉进程
        process = psutil.Process(pid)
        #print(process)
        name = process.name()
        opt = '警告'
        # 忽略不需要处理的进程
        if process.name() not in ignore_processes:
            #process.kill()
            kill_count += 1
            opt = '杀死'
        print('[{:0>2}] {}: 进程:{:<20} ID:{:<10} 页面错误数量:{}'.format(i+1, opt, name, pid, page_faults))
    print('本次共杀死{}个进程'.format(kill_count))
    
    """
        if process.name() == 'mintty.exe':
            # 找到目标进程
            print(process)
            mem_info = process.memory_info()
            page_faults = mem_info.num_page_faults
            print(page_faults)
            break
    """