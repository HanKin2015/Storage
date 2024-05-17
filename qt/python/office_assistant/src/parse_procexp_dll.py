# -*- coding: utf-8 -*-
"""
文 件 名: Ui_Database.py
文件描述: 数据库界面
作    者: HanKin
创建日期: 2024.02.27
修改日期：2024.02.27

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time

def read_first_column(file_path):
    first_column_set = set()
    with open(file_path, "r", encoding="utf-8") as f:
        for row in f:
            column_list = row.split()
            if len(column_list):
                file_name = column_list[0]
                #print(file_name)
                if file_name[-3:] not in ["exe", "dll"]:
                    first_column_set.add(file_name)
    #print(first_column_set)
    return first_column_set

def calculate_intersection(set1, set2):
    # 使用 - 操作符计算交集
    intersection = set1 - (set1 - set2)
    #print(intersection) 
    
    # 使用 set.intersection() 方法计算交集
    intersection = set1.intersection(set2)
    print(intersection)

def calculate_difference(set1, set2):
    difference = set1 - set2
    print(difference)

def main():
    """主函数
    """
    
    machine_file_paths = [r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client.exe物理机.txt", r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client.exe物理机子1.txt", r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client.exe物理机子2.txt", r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client.exe物理机子3.txt",r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client.exe物理机子4新.txt"]
    machine_set = set()
    for machine_file_path in machine_file_paths:
        temp = read_first_column(machine_file_path)
        machine_set.update(temp)
    
    virtual_file_paths = [r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client虚拟机不装wacom (2).txt",r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client虚拟机不装wacom子1(1).TXT",r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client虚拟机不装wacom子2(1).TXT",r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client虚拟机不装wacom子3(1).TXT",r"D:\Users\Administrator\Desktop\对比\HSUCF.Cef.Wpf.Client虚拟机不装wacom子4(1).TXT"]
    virtual_set = set()
    for virtual_file_path in virtual_file_paths:
        temp = read_first_column(virtual_file_path)
        virtual_set.update(temp)
    
    #calculate_intersection(machine_set, virtual_set)
    
    print("物理机:")
    calculate_difference(machine_set, virtual_set)
    print("\n\n")
    print("虚拟机:")
    calculate_difference(virtual_set, machine_set)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))