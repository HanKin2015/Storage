# -*- coding: utf-8 -*-
"""
文 件 名: rename_file_suffixes.py
文件描述: 重命名文件后缀
作    者: HanKin
创建日期: 2022.11.28
修改日期：2022.11.28

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import stat
import time
  
if __name__ == '__main__':
    """程序入口
    """
    
    file_dir = './'
    file_suffix = '.apk'
    new_suffix = '.znds'
    
    for root, dirs, files in os.walk(file_dir):  
        for file in files:  
            if os.path.splitext(file)[1] == file_suffix:  
                new_file = os.path.splitext(file)[0] + new_suffix
                os.rename(file, new_file)
                print('{} was renamed to {}'.format(file, new_file))