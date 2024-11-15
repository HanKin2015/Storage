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
from log import logger
import datetime
import subprocess
import panda as pd

def show_error(message):
    # 创建一个隐藏的主窗口
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口

    # 弹出错误提示框
    messagebox.showerror("错误", message)
    logger.info(message)

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
                logger.info("current suffix[{}] file: {}".format(suffix, file))
                count += 1
                file_path = os.path.join(root, file)
    logger.info("there are {} files with {} suffix".format(count, suffix_list))

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
        logger.info("idVendor:idProduct <<===>> {}\n".format(vpid)) 
    else:
        #logger.info("未找到匹配项") 
        pass
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
        logger.info('{} is a zip file({})'.format(file_name, suffix))
    else:
        logger.info('{} is not a zip file({})'.format(file_name, suffix))
        return None

    loc = file_name.rfind('_')
    sn = file_name[loc+1:loc+11]
    sn_pre3 = sn[:3]
    logger.info('sn is {}, prefix is {}'.format(sn, sn_pre3))
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
                logger.info("Warning: Found a member with an empty filename, skipping. {}".format(member.filename))
                continue
            original_filename = member.filename
            # 替换 Windows 不支持的字符
            sanitized_filename = original_filename.replace(':', '_')
            filename = sanitized_filename.encode('cp437').decode('gbk')
            #logger.info(''.format(filename))
            zip_ref.extract(member, path=extract_path, pwd=None) 
            src = os.path.join(extract_path, sanitized_filename)
            dst = os.path.join(extract_path, filename)
            #logger.info(f"Renaming {src} to {dst}")
            os.rename(src, dst)

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
                logger.info('this is kernel log file: {}'.format(file_path))
                files_path['kernel_log_file_path'] = file_path
            if file in ['spicec.log', 'logcat.txt']:
                file_path = os.path.join(root, file)
                logger.info('this is client log file: {}'.format(file_path))
                files_path['client_log_file_path'] = file_path
    kernel_log_file_name = os.path.basename(files_path.get('kernel_log_file_path', ''))
    if kernel_log_file_name == 'dmesg.txt':
        files_path['client_type'] = 'android'
    else:
        files_path['client_type'] = 'linux'
    return files_path

def parse_kernel_log(kernel_log_file_path):
    """
    解析内核日志
    :param kernel_log_file_path: 内核日志文件路径
    :return
    """
    logger.info("\n\n\t\t=======================<< kernel log >>=======================")
    vpid_set    = set()
    error_cnt   = 0
    emi_cnt     = 0
    reset_cnt   = 0
    connect_cnt = 0
    keywords    = ["USB device number", "USB disconnect", "New USB device found"]
    with open(kernel_log_file_path, 'r', errors='replace') as f:
        for line in f:
            line = line.strip()
            # 电磁干扰
            if "(EMI" in line:
                emi_cnt += 1
            # 设备枚举失败
            if "error -71" in line or "device descriptor" in line:
                error_cnt += 1
            if "reset" in line:
                reset_cnt += 1
            if any(keyword in line for keyword in keywords):
                logger.info(line)
                connect_cnt += 1
                vpid = parse_vpid(line)
                if vpid:
                    vpid_set.add(vpid)
    logger.info(vpid_set)
    if emi_cnt > 0:
        show_error('kernel log file has {} <EMI> keyword（电磁干扰）'.format(emi_cnt))
    if error_cnt > 5:
        show_error('kernel log file has {} <device descriptor read/64, error -71>（枚举失败）'.format(error_cnt))
    if reset_cnt > 3:
        show_error('kernel log file has {} <reset high-speed>（reset名单）'.format(reset_cnt))
    if connect_cnt > 150:
        show_error('kernel log file has {:.0f} <connect disconnect>（频繁断连）'.format(connect_cnt/3))

def detect_encoding(file_path):
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    logger.info(result['encoding'])
    return result['encoding']

def parse_android_list(line):
    """
    解析安卓名单
    """
    matches = re.findall(r'vid:pid = ([0-9a-fA-F]+):([0-9a-fA-F]+)', line)
    if matches:
        return '{}:{}'.format(matches[0][0], matches[0][1])

def parse_android_client_log(client_log_file_path):
    """
    解析安卓客户端日志
    :param client_log_file_path: 客户端日志文件路径
    :return
    """
    logger.info("\n\n\t\t=======================<< client log >>=======================")
    #encoding = detect_encoding(client_log_file_path)
    white_list = set()
    black_list = set()
    with open(client_log_file_path, 'r', encoding='utf-8', errors='ignore') as f:  # 限制异常
        for line in f:
            line = line.strip()
            if "映射成功" in line:
                logger.info(line)
            if "WhiteList" in line:
                vpid = parse_android_list(line)
                white_list.add(vpid)
            if "BlackList" in line:
                vpid = parse_android_list(line)
                black_list.add(vpid)
    logger.info('白名单：{}'.format(white_list))
    logger.info('黑名单：{}'.format(black_list))

def parse_linux_list(line):
    """
    解析安卓名单
    """
    matches = re.findall(r'device ([0-9a-fA-F]+):([0-9a-fA-F]+)', line)
    if matches:
        return '{}:{}'.format(matches[0][0], matches[0][1])

def parse_linux_client_log(client_log_file_path):
    """
    解析Linux客户端日志
    :param client_log_file_path: 客户端日志文件路径
    :return
    """
    logger.info("\n\n\t\t=======================<< client log >>=======================")
    logger.info("clien log file path: {}".format(client_log_file_path))
    #encoding = detect_encoding(client_log_file_path)
    white_list = set()
    black_list = set()
    with open(client_log_file_path, 'r', encoding='utf-8', errors='ignore') as f:  # 限制异常
        for line in f:
            line = line.strip()
            if "redir device succeed" in line:
                logger.info(line)
            if "in black list" in line:
                vpid = parse_linux_list(line)
                black_list.add(vpid)
    logger.info('黑名单：{}'.format(black_list))

def parse_log(extract_path):
    """
    解析日志
    :param extract_path: 解压路径
    :return
    """
    files_path = find_specified_files_path(extract_path)
    logger.info(files_path)
    client_type = files_path.get('client_type', '')

    # 解析内核日志
    kernel_log_file_path = files_path.get('kernel_log_file_path', '')
    parse_kernel_log(kernel_log_file_path)
    
    # 解析客户端日志
    client_log_file_path = files_path.get('client_log_file_path', '')
    if client_type == 'android':
        parse_android_client_log(client_log_file_path)
    else:
        parse_linux_client_log(client_log_file_path)

def notepad_plus_plus_open_file():
    """
    使用notepad++打开文件
    """
    notepad_plus_plus_path = r'C:\Program Files\Notepad++\notepad++.exe'
    document_path = 'C:\\path\\to\\your\\document.txt'

    if os.path.exists(notepad_plus_plus_path):
        command = [notepad_plus_plus_path, './log_parse_result.txt']
        subprocess.Popen(command)
    else:
        print(f"文档 {document_path} 不存在。")

def main():
    """主函数
    """
    
    #logger.info(sys.argv)
    argv_cnt = len(sys.argv)
    if argv_cnt != 2:
        logger.info('argument count is not two, need log file path')
        return

    zip_file_path = sys.argv[1]
    sn = get_client_type(zip_file_path)
    if sn is None:
        return

    extract_path = 'tmp'
    unzip_file(zip_file_path, extract_path)
    parse_log(extract_path)
    notepad_plus_plus_open_file()

def debug():
    """调试
    """
    pass

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting({}) ********'.format(datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")))
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    logger.info('******** process spend {} s(20241104) ********'.format(round(end_time - start_time, 3)))
    #os.system("pause")
    
