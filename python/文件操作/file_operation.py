# -*- coding: utf-8 -*-
"""
文 件 名: file_operation.py
文件描述: 文件的相关操作
作    者: HanKin
创建日期: 2023.09.28
修改日期：2023.09.28

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import shutil
        
if __name__ == '__main__':
    old_name = 'old_name.txt'
    new_name = 'new_name.txt'

    shutil.copy(old_name, new_name) # 复制一份新文件并重命名
    os.rename(new_name, old_name)   # 重命名文件
    os.remove(old_name)             # 删除文件