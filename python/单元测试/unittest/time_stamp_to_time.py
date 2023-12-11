# -*- coding: utf-8 -*-
"""
文 件 名: time_stamp_to_time.py
文件描述: 把时间戳转化为时间
作    者: HanKin
创建日期: 2022.02.17
修改日期：2022.02.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time

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