# -*- coding: utf-8 -*-
"""
文 件 名: log.py
文件描述: 日志文件，支持文件和控制台同时输出
作    者: Hejian
创建日期: 2022.05.31
修改日期：2022.05.31
Copyright (c) 2022 Hejian. All rights reserved.
"""

import logging
import os

# 创建结果备份文件夹
if not os.path.exists('./backup/'):
    os.makedirs('./backup/')

# 创建日志文件夹
if not os.path.exists('./log/'):
    os.makedirs('./log/')
# 配置日志
logger = logging.getLogger()
logger.setLevel(logging.INFO)
LOG_FILE_PATH = './log/module.log'

# 日志控制台输出
stream_handler = logging.StreamHandler()
stream_format = logging.Formatter('%(asctime)s %(pathname)s[%(funcName)s:%(lineno)d] %(levelname)s: %(message)s', '%Y-%m-%d %H:%M:%S')
stream_handler.setFormatter(stream_format)
logger.addHandler(stream_handler)

# 日志文件输出
file_handler = logging.FileHandler(LOG_FILE_PATH, mode='a', encoding='UTF-8')
logging_format = logging.Formatter('%(asctime)s %(pathname)s[%(funcName)s:%(lineno)d] %(levelname)s: %(message)s', '%Y-%m-%d %H:%M:%S')
file_handler.setFormatter(logging_format)
logger.addHandler(file_handler)

# 开启debug日志方法（创建一个debug文件即可）
if os.path.exists('./log/debug'):
    logger.setLevel(logging.DEBUG)

