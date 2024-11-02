# -*- coding: utf-8 -*-
"""
文 件 名: log_file_parse_tool.py
文件描述: 日志文件解析工具
备    注: 
作    者: HanKin
创建日期: 2024.10.08
修改日期：2024.10.08

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
import time
import re
import sys
import zipfile
import tkinter as tk
from tkinter import messagebox
import chardet
import shutil

def show_error(message):
    # 创建一个隐藏的主窗口
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口

    # 弹出错误提示框
    messagebox.showerror("错误", message)

    # 销毁主窗口
    root.destroy()

def list_specified_suffix_files(dir_path, suffix_list):
    """
    列出指定后缀的文件
    """
    count = 0
    for root, dirs, files in os.walk(dir_path, topdown=False):
        for file in files:
            suffix = file.split(".")[-1]
            if suffix in suffix_list:
                print("current suffix[{}] file: {}".format(suffix, file))
                count += 1
                file_path = os.path.join(root, file)
    print("there are {} files with {} suffix".format(count, suffix_list))

def parse_vpid(insert_line):
    """从设备插入内容中解析vid和pid
    """
    vpid = None

    # 使用正则表达式匹配 idVendor 和 idProduct
    matches = re.findall(r'idVendor=([0-9a-fA-F]+), idProduct=([0-9a-fA-F]+)', insert_line)

    # 如果找到匹配项，提取 idVendor 和 idProduct 的值
    if matches:
        idVendor = matches[0][0]
        idProduct = matches[0][1]
        vpid = "{}:{}".format(idVendor, idProduct)
        print("idVendor:idProduct <<===>> {}\n".format(vpid)) 
    else:
        print("未找到匹配项") 
    return vpid

def get_client_type(file_path):
    """通过sn码确定客户端类型
    发现其实直接找相关的文件名即可，找到哪个就解析哪个日志文件
    """
    # 取绝对路径最后一个文件名
    file_name = os.path.basename(file_path)
    # 取后缀
    suffix = file_name.split('.')[-1]
    
    if suffix == 'zip':
        print('{} is a zip file({})'.format(file_name, suffix))
    else:
        print('{} is not a zip file({})'.format(file_name, suffix))
        return None

    loc = file_name.rfind('.')
    sn = file_name[loc-10:loc]
    sn_pre3 = sn[:3]
    print('sn is {}, prefix is {}'.format(sn, sn_pre3))
    return sn

def unzip_file(zip_file_path, extract_path):
    """解压文件
    在解压缩每个成员之前，检查 member.filename 是否为空。如果为空，则跳过该条目
    """
    if os.path.exists(extract_path):
        shutil.rmtree(extract_path)
    os.makedirs(extract_path)
    
    with zipfile.ZipFile(zip_file_path, 'r') as zip_ref:
        for member in zip_ref.infolist():
            # 检查文件名是否为空
            if not member.filename:
                print("Warning: Found a member with an empty filename, skipping. {}".format(member.filename))
                continue
            filename = member.filename.encode('cp437').decode('gbk')
            #print(''.format(filename))
            zip_ref.extract(member, path=extract_path, pwd=None) 
            os.rename(os.path.join(extract_path, member.filename), os.path.join(extract_path, filename)) 

def find_specified_files_path(dir_path):
    """
    查找指定的文件路径
    :param dir_path: 文件夹路径
    :return files_path: 文件路径
    """
    files_path = dict()
    for root, dirs, files in os.walk(dir_path, topdown=False):
        for file in files:
            if file in ['system.log', 'dmesg.txt']:
                file_path = os.path.join(root, file)
                print('this is kernel log file: {}'.format(file_path))
                files_path['kernel_log_file_path'] = file_path
            if file in ['spicec.log', 'logcat.txt']:
                file_path = os.path.join(root, file)
                print('this is client log file: {}'.format(file_path))
                files_path['client_log_file_path'] = file_path
    return files_path

def parse_kernel_log(kernel_log_file_path):
    """
    解析内核日志
    :param kernel_log_file_path: 内核日志文件路径
    :return
    """
    print("\n\n\t\t=======================<< kernel log >>=======================")
    vpid_set = set()
    with open(kernel_log_file_path, 'r', errors='replace') as f:
        for line in f:
            # 电磁干扰
            if "EMI" in line:
                print(line)
                show_error('kernel log file has <EMI> keyword')
                return
            
            # 设备枚举失败
            if "error -71" in line:
                print(line)
                show_error('kernel log file has <device descriptor read/64, error -71>')
                return

            if "USB device number" in line:
                line = line.strip()
                print(line)
            if "USB disconnect" in line:
                line = line.strip()
                print(line)
            if "New USB device found" in line:
                line = line.strip()
                print(line)
                vpid = parse_vpid(line)
                if vpid:
                    vpid_set.add(vpid)
    print(vpid_set)

def detect_encoding(file_path):
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    print(result['encoding'])
    return result['encoding']

def parse_client_log(client_log_file_path):
    """
    解析客户端日志
    :param client_log_file_path: 客户端日志文件路径
    :return
    """
    print("\n\n\t\t=======================<< client log >>=======================")
    #encoding = detect_encoding(client_log_file_path)
    with open(client_log_file_path, 'r', encoding='utf-8', errors='ignore') as f:  # 限制异常
        for line in f:
            if "映射成功" in line:
                print(line)
            if "redir device succeed" in line:
                print(line)

def parse_log(extract_path):
    """
    解析日志
    :param extract_path: 解压路径
    :return
    """
    files_path = find_specified_files_path(extract_path)
    print(files_path)

    # 解析内核日志
    kernel_log_file_path = files_path.get('kernel_log_file_path', '')
    parse_kernel_log(kernel_log_file_path)
    

    # 解析客户端日志
    client_log_file_path = files_path.get('client_log_file_path', '')
    parse_client_log(client_log_file_path)

def main():
    """主函数
    """
    
    #print(sys.argv)
    argv_cnt = len(sys.argv)
    if argv_cnt != 2:
        print('argument count is not two, need log file path')
        return

    zip_file_path = sys.argv[1]
    sn = get_client_type(zip_file_path)
    if sn is None:
        return

    extract_path = 'tmp'
    unzip_file(zip_file_path, extract_path)
    parse_log(extract_path)

def debug():
    """调试
    """
    directory_path = r'D:\Users\Administrator\My Document\WXWork\1688854308416542\Cache\File\2024-05'
    #directory_path = r'D:\Users\Administrator\Desktop'
    #list_specified_suffix_files(directory_path, ['docx', 'doc'])
    read_udev_info_from_linux_box()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    os.system("pause")
    
