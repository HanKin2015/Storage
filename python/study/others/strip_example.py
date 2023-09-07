# -*- coding: utf-8 -*-
"""
文 件 名: strip_example.py
文件描述: strip函数
作    者: HanKin
创建日期: 2023.09.06
修改日期：2023.09.06

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import os
import sys

def main():
    """主函数
    """
    
    strs = 'abbbcabb'
    print(strs.strip('ab'))     //c
    print(strs.lstrip('ab'))    //cabb
    print(strs.rstrip('ab'))    //abbbc

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))