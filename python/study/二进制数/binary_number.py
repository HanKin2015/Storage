# -*- coding: utf-8 -*-
"""
文 件 名: brute_ftp_by_dict.py
文件描述: py如何打印 1-10的 二进制数 就是8位数字
作    者: HanKin
创建日期: 2022.09.29
修改日期：2022.09.29

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time

def main():
    for i in range(1, 11):
        print(f'{i} = {i:08b}')

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))