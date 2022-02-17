# -*- coding: utf-8 -*-
"""
文 件 名: test_common.py
文件描述: 测试python公共自用库
作    者: HanKin
创建日期: 2022.02.17
修改日期：2022.02.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

from common import *

if __name__ == '__main__':
    print(time_stamp_to_time(1479264792))
    
    file_path = '.\\读写文件.txt'
    print(get_file_size(file_path))
    print(get_file_access_time(file_path))
    print(get_file_create_time(file_path))
    print(get_file_modify_time(file_path))