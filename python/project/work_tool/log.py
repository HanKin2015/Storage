# -*- coding: utf-8 -*-
"""
文 件 名: log.py
文件描述: 日志文件，支持文件和控制台同时输出
用    法: from log import logger
          logger.info()
          logger.warning()
          logger.error()
          logger.debug()
作    者: HanKin
创建日期: 2022.05.31
修改日期：2024.11.04
Copyright (c) 2023 HanKin. All rights reserved.
"""

import logging
import os

# 配置日志
logger = logging.getLogger()
logger.setLevel(logging.INFO)
LOG_FILE_PATH = './simulate_mouse_clicks.txt'

# 自定义日志路径
def setPath(log_file_path):
    global LOG_FILE_PATH
    LOG_FILE_PATH = log_file_path

# 日志控制台输出（filename）
stream_handler = logging.StreamHandler()
stream_format = logging.Formatter('%(message)s')
stream_handler.setFormatter(stream_format)
logger.addHandler(stream_handler)

# 日志文件输出
file_handler = logging.FileHandler(LOG_FILE_PATH, mode='w', encoding='UTF-8')
logging_format = logging.Formatter('%(message)s')
file_handler.setFormatter(logging_format)
logger.addHandler(file_handler)

# 开启debug日志方法（创建一个debug文件即可）
if os.path.exists('./log/debug'):
    logger.setLevel(logging.DEBUG)

