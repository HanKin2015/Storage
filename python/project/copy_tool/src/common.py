# -*- coding: utf-8 -*-
"""
文 件 名: ftp_operation.py
文件描述: ftp相关操作
作    者: HanKin
创建日期: 2020.11.01
修改日期：2022.08.15

Copyright (c) 2022 HanKin. All rights reserved.
"""

import win32api
import win32con
from tkinter import filedialog, messagebox  # 这两个需要单独导入
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button  # 导入ttk模块中的指定几个组件
import tkinter
from editor_style import theme_color, ICONS  # 这里就是从之前命名的文件中导入两个参数
import tkinter.font
import os
import ftplib
import base64
from icon import icon_img
import md5
import logging
import sys
import configparser
from log import *
from entrywithplaceholder import EntryWithPlaceholder

# 软件名称
app_name = '拷贝工具'

# 工作目录
work_path = 'D:/copy_tool/'

# 软件日志路径
log_path = 'D:/copy_tool/copy_tool.log'

# 中转文件名称
temp_file_name = 'copy_words.txt'

# 云端指定中转站文件夹路径
remote_dir_path = '/copy/'

# 文件下载路径
download_path = 'D:/copy_tool/download/'

# 常用的保留TCP端口号有：HTTP 80，FTP 20/21，Telnet 23，SMTP 25，DNS 53等。
# 用于FTP服务的21端口
ftp_port = 21

# 默认ftp服务器ip地址
ftp_ip = '127.0.0.1'

# 默认ftp服务器用户名
ftp_username = 'hankin'

# 默认ftp服务器密码
ftp_password = 'hankin'

# 配置文件
config_path = 'D:/copy_tool/config.ini'

# 帮助文件路径
help_file_path = '../config/help.txt'

# 关于文件路径
about_file_path = '../config/about.txt'

# 更新日志文件路径
update_file_path = '../config/update.txt'

# 软件更新日志路径
update_log_path = 'D:/copy_tool/update_log.log'

# 本地下载路径是否存在，不存在则创建，顺手创建工作目录
if not os.path.exists(download_path):
    os.makedirs(download_path)
