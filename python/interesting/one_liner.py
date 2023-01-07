# -*- coding: utf-8 -*-
"""
文 件 名: one_liner.py
文件描述: Python单行代码
作    者: HanKin
创建日期: 2022.12.26
修改日期：2022.12.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time

def main():
    

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    