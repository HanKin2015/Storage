# -*- coding: utf-8 -*-
"""
文 件 名: common.py
文件描述: python公共自用库
作    者: HanKin
创建日期: 2022.02.17
修改日期：2022.02.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import argparse
import logging
import hashlib

def time_stamp_to_time(time_stamp):
    """把时间戳转化为时间

    1479264792 to 2016-11-16 10:53:12
    
    Parameters
    ------------
    time_stamp : str
        时间戳

    Returns
    -------
    str
        返回指定格式化的时间
    """
    
    time_struct = time.localtime(time_stamp)
    return time.strftime('%Y-%m-%d %H:%M:%S', time_struct)

def get_file_size(file_path):
    """获取文件的大小

    结果保留两位小数，单位为KB
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的大小
    """

    file_size = os.path.getsize(file_path)
    file_size = file_size / float(1024)
    return round(file_size, 2)

def get_file_access_time(file_path):
    """获取文件的访问时间

    获取文件的访问时间
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的访问时间
    """

    time_stamp= os.path.getatime(file_path)
    return time_stamp_to_time(time_stamp)

def get_file_create_time(file_path):
    """获取文件的创建时间

    获取文件的创建时间
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的创建时间
    """

    time_stamp= os.path.getctime(file_path)
    return time_stamp_to_time(time_stamp)

def get_file_modify_time(file_path):
    """获取文件的修改时间

    获取文件的修改时间
    
    Parameters
    ------------
    file_path : str
        文件路径

    Returns
    -------
    str
        返回文件的修改时间
    """

    time_stamp= os.path.getmtime(file_path)
    return time_stamp_to_time(time_stamp)
















