# -*- coding: utf-8 -*-
"""
文 件 名: page_error_increment.py
文件描述: 页面错误增量导致程序卡死
作    者: HanKin
创建日期: 2024.01.09
修改日期：2024.01.09

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
import win32com.client
import pythoncom
import gc
import tracemalloc
import psutil
import subprocess

def get_udev_info_list():
    """
    更换成函数后错误增量就变成21左右了，不是函数才2左右
    """
    wmi = win32com.client.GetObject("winmgmts:")
    for pnp in wmi.InstancesOf("Win32_PnPEntity"):
        if 'USB\\VID' in pnp.DeviceID and pnp.DeviceID.count('&') <= 4:
            print('----', pnp.DeviceID.count('&'))
            for prop in pnp.Properties_:
                print('{} : {}'.format(prop.Name, prop.Value))
                #pass
    del wmi

def get_udev_info_list1():
    """
    使用更具体的WQL语句
    """
    wmi = win32com.client.GetObject("winmgmts:")
    # 注意：在WQL字符串中使用四个反斜杠来转义反斜杠
    # 注意：在WQL字符串中使用 %% 而不是 %
    query = "SELECT * FROM Win32_PnPEntity WHERE DeviceID LIKE '%%USB\\\\VID%%'"
    for pnp in wmi.ExecQuery(query):
        # 这里你可以根据需要进一步过滤，例如检查DeviceID中的'&'数量
        if pnp.DeviceID.count('&') <= 4:
            for prop in pnp.Properties_:
                print('{} : {}'.format(prop.Name, prop.Value))

def get_udev_info_list2():
    """
    强制运行垃圾回收器
    """
    # 初始化COM库
    pythoncom.CoInitialize()
    
    wmi = win32com.client.GetObject("winmgmts:")
    del wmi
    gc.collect()    # 强制运行垃圾回收器
    
    # 释放COM资源
    pythoncom.CoUninitialize()

def get_udev_info_list3():
    """
    使用 tracemalloc 来监控内存使用情况
    """
    # 初始化COM库
    pythoncom.CoInitialize()
    
    wmi = win32com.client.GetObject("winmgmts:")
    del wmi
    gc.collect()    # 强制运行垃圾回收器
    
    # 释放COM资源
    pythoncom.CoUninitialize()

def get_udev_info_list4(wmi):
    """
    传递wmi对象，这种方法可部分解决内存泄露问题，但是还是会有一丁点的页面错误增量
    可能是设备造成，把设备去掉后就没有了，可能是变量问题
    """
    count = 0
    query = "SELECT * FROM Win32_PnPEntity WHERE DeviceID LIKE '%%USB\\\\VID%%'"
    for pnp in wmi.ExecQuery(query):
        # 这里你可以根据需要进一步过滤，例如检查DeviceID中的'&'数量
        if pnp.DeviceID.count('&') <= 4:
            for prop in pnp.Properties_:
                #print('{} : {}'.format(prop.Name, prop.Value))
                pass
            count += 1
    print(count)

def get_udev_info_list5():
    """
    psutil库来监控内存使用情况，确认是否存在内存泄露情况
    虽然内存增长的很慢，但还是有所增长，并且在win10系统中WMI provider Host占用CPU很高，电源使用情况也很高，导致界面直接卡死了
    内存从19.16MB涨到了19.68MB，后面增速越快
    
    后面我又测试了去掉这一行代码测试，内存从16.71MB到16.75MB
    """
    #wmi = win32com.client.GetObject("winmgmts:")
    #del wmi
    x = 1 + 2

def get_udev_info_list6():
    """
    使用 subprocess 模块来调用命令行工具 wmic 来获取，也不存在内存泄露
    """
    # 构建 wmic 命令
    cmd = 'wmic path Win32_PnPEntity WHERE "DeviceID LIKE \'%USB\\\\VID%\'" get /format:list'
    
    try:
        # 执行命令并获取输出
        output = subprocess.check_output(cmd, shell=True)
        # 将输出解码为字符串
        output = output.decode('utf-8', 'ignore')
        print('*' * 50)
        print(output)
        print('*' * 50)
        
        # 分割输出以获取单独的属性
        properties = output.strip().split('\r\r\n')
        
        # 过滤掉空行和不需要的属性
        #properties = [prop for prop in properties if prop.strip() and prop.count('&') <= 4]
        tmp_lst = []
        for prop in properties:
            if prop.strip() and prop.count('&') <= 4:
                print(prop.count('&'))
                tmp_lst.append(prop)
        properties = tmp_lst
        
        # 打印属性
        for prop in properties:
            print(prop)
    except subprocess.CalledProcessError as e:
        print("An error occurred while running the command: ", e)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    # 开始跟踪内存分配
    #tracemalloc.start()
    
    # 获取当前进程
    process = psutil.Process()
    
    for i in range(1):
        get_udev_info_list()
        get_udev_info_list6()
        time.sleep(0.2)
        
        # 获取当前进程的内存信息
        mem_info = process.memory_info()
        print(f"{i} Memory usage: {mem_info.rss / 1024**2:.2f} MB")  # rss是常驻内存集大小
        
        # 每次循环后，打印内存分配情况
        #current, peak = tracemalloc.get_traced_memory()
        #print(f"Current memory usage is {current / 10**6}MB; Peak was {peak / 10**6}MB")

    # 停止跟踪内存分配
    #tracemalloc.stop()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
