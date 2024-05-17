# -*- coding: utf-8 -*-
"""
文 件 名: batch_nest_exec_command.py
文件描述: 批量嵌套执行命令
备    注: 查询各个客户端的内核日志中是否存在异常
作    者: HanKin
创建日期: 2024.04.29
修改日期：2024.04.29

Copyright (c) 2023 HanKin. All rights reserved.
"""
import paramiko
import re
import os
import configparser
import chardet
import logging
import datetime

# 日志模块
logger = logging.getLogger()
logger.setLevel(logging.INFO)
log_file_path = "./check_EMI_log.log"
stream_handler = logging.StreamHandler()
stream_format = logging.Formatter('%(asctime)s %(filename)s[%(funcName)s:%(lineno)d] %(levelname)s: %(message)s', '%Y-%m-%d %H:%M:%S')
stream_handler.setFormatter(stream_format)
logger.addHandler(stream_handler)
file_handler = logging.FileHandler(log_file_path, mode='a') # 存在乱码，不清楚是不是这个导致encoding='UTF-8'
logging_format = logging.Formatter('%(asctime)s %(filename)s[%(funcName)s:%(lineno)d] %(levelname)s: %(message)s', '%Y-%m-%d %H:%M:%S')
file_handler.setFormatter(logging_format)
logger.addHandler(file_handler)

# 帐户信息读取
config_parser = configparser.ConfigParser(allow_no_value=True, strict=False) # 允许重复值
conf_path = "conf.ini"
def detect_encoding(file_path):
    """获取文件编码格式
    """
    with open(file_path, 'rb') as f:
        rawdata = f.read()
    result = chardet.detect(rawdata)
    logger.debug(result['encoding'])
    return result['encoding']
encoding = detect_encoding(conf_path)
config_parser.read(conf_path, encoding=encoding)
server_ip = config_parser.get("server", "ip")
server_port = config_parser.get("server", "port")
server_user = config_parser.get("server", "user")
server_pwd = config_parser.get("server", "pwd")
server_port = int(server_port)
logger.debug(server_ip, server_port, server_user, server_pwd)
logger.debug(type(server_port))
count_threshold = config_parser.get("threshold", "count")
count_threshold = int(count_threshold)

# 创建SSH客户端对象并建立连接
ssh_client = paramiko.SSHClient()
ssh_client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh_client.connect(server_ip, server_port, server_user, server_pwd)

# 建立一个sftp客户端对象，通过ssh transport操作远程文件
transport = paramiko.Transport(server_ip, server_port)
transport.connect(username=server_user, password=server_pwd)
sftp_client = paramiko.SFTPClient.from_transport(transport)

def exec_command(command, timeout=3000):
    """执行命令
    """
    stdin, stdout, stderr = ssh_client.exec_command(command, timeout=timeout)
    output = stdout.read().decode('utf-8')
    error = stderr.read().decode('utf-8')
    logger.debug(command)
    logger.debug(error)
    #return output.replace("\n", "")   # 需要考虑到有换行符的存在
    return output

def count_today_occurrence_number(log_content):
    """统计今天发生次数
    """
    today = datetime.datetime.now().date()
    day_number = today.day
    logger.debug("today date is {}".format(day_number))
    
    log_list = log_content.split("\n")
    today_count = 0
    for row in log_list:
        try:
            log_day = row.split()[2]
            if int(log_day) == day_number:
                today_count += 1
        except Exception as err:
            logger.error("row is {}, {}".format(row, err))
    return today_count

def android_count_today_occurrence_number(log_content):
    """统计今天发生次数（存在统计到上个月的今天问题）
    """
    today = datetime.datetime.now().date()
    day_number = today.day
    logger.debug("today date is {}".format(day_number))
    
    log_list = log_content.split("\n")
    today_count = 0
    for row in log_list:
        try:
            log_day = row.split()[0]
            if int(log_day[-2:]) == day_number:
                today_count += 1
        except Exception as err:
            logger.error("row is {}, {}".format(row, err))
    return today_count

def android_nest_exec_command(client_sn):
    """嵌套执行命令
    """
    #command = "echo '%s' | sudo -S tcmgrutil debug -k %s -o | awk 'NR == 2{print $5}'" % (server_pwd, client_sn)
    # 字符串中的特殊字符：当字符串使用了大括号（{}）作为占位符，如果字符串中包含大括号，可能会导致格式化出错。
    # 你可以尝试使用双大括号（{{}}）来转义大括号，例如'{{}}'。
    command = "echo {} | sudo -S tcmgrutil debug -k {} -o | awk 'NR == 2{{print $5}}'".format(server_pwd, client_sn)
    addr = exec_command(command)
    if len(addr) == 0:
        logger.error("box maybe offline, {}".format(client_sn))
        return 0, None
    addr = addr.replace("\n", "")
    
    exec_command("adb disconnect")
    command = "adb connect {}".format(addr)
    exec_command(command)
    
    command = "echo {} | sudo -S adb -s {} shell dmesg -T | grep 'USB disconnect'".format(server_pwd, addr)
    ret = exec_command(command)
    ret = ret.strip("\n")
    today_count = android_count_today_occurrence_number(ret)
    logger.info("today USB disconnect number -- {}".format(today_count))
    
    # 获取EMI日志
    command = "echo {} | sudo -S adb -s {} shell dmesg -T | grep EMI | tail -n 10".format(server_pwd, addr)
    ret = exec_command(command)
    if len(ret):
        ret = ret.strip("\n")
        logger.info(ret)
        logger.debug(client_sn)
        return today_count, True
    return today_count, False

def debian_nest_exec_command(client_sn):
    """嵌套执行命令（需要输入密码可借助sshpass工具）
    """
    client_pwd = "xxxx"
    sshpass_filepath = "/stmp/sshpass"
    
    command = "echo {} | sudo -S debug.sh -s {}".format(server_pwd, client_sn)
    login_info = exec_command(command)
    logger.debug(login_info)
    try:
        port = re.search(r"ssh root@localhost -p (.*)", login_info).group(1)
    except Exception as err:
        logger.error("box maybe offline, {}".format(err))
        return 0, None
    
    # 上传sshpass文件
    sftp_client.put("sshpass", sshpass_filepath)
    
    # 给sshpass赋予可执行权限
    command = "echo '%s' | sudo -S chmod +x %s" % (server_pwd, sshpass_filepath)
    exec_command(command)

    # 登录到客户端
    command = "echo '%s' | sudo -S %s -p '%s' ssh -o StrictHostKeyChecking=no root@localhost -p %s" % (
        server_pwd, sshpass_filepath, client_pwd, port)
    exec_command(command)

    # 嵌套执行命令
    command = "echo '%s' | sudo -S %s -p '%s' ssh root@localhost -p %s dmesg -T | grep 'USB disconnect'" % (
        server_pwd, sshpass_filepath, client_pwd, port)
    ret = exec_command(command)
    ret = ret.strip("\n")
    today_count = count_today_occurrence_number(ret)
    logger.info("today USB disconnect number -- {}".format(today_count))
    
    # 获取EMI日志
    command = "echo '%s' | sudo -S %s -p '%s' ssh root@localhost -p %s dmesg -T | grep EMI | tail -n 10" % (
        server_pwd, sshpass_filepath, client_pwd, port)
    ret = exec_command(command)
    if len(ret):
        ret = ret.strip("\n")
        logger.info(ret)
        logger.debug(client_sn)
        return today_count, True
    return today_count, False

# 获取客户端列表
with open("client_sn.txt", "r") as f:
    fault_client_sns = []
    disconnect_client_sns = []
    for index, client_sn in enumerate(f):
        logger.info("*" * 80)
        client_sn = client_sn.strip("\n")
        logger.info("index {} --- {}".format(index+1, client_sn))
        if client_sn[:3] in ["74Z", "7AW", "7JZ"]:
            today_count, ret = android_nest_exec_command(client_sn)
        else:
            today_count, ret = debian_nest_exec_command(client_sn)
        if ret:
            fault_client_sns.append(client_sn)
        if today_count > count_threshold:
            disconnect_client_sns.append((client_sn, today_count))
    logger.info(fault_client_sns)
    logger.info(disconnect_client_sns)

# 关闭连接
ssh_client.close()
sftp_client.close()

os.system("pause")
