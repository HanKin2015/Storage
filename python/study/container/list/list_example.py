# -*- coding: utf-8 -*-
"""
文 件 名: list_example.py
文件描述: 学习list列表
作    者: HanKin
创建日期: 2023.10.19
修改日期：2023.10.19

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

def main():
    """主函数
    """
    
    a = [1, 2, 3, 4]
    b = [6, 7, 8]
    c = []
    c.extend(a)
    c.extend(b)
    print(c)    # [1, 2, 3, 4, 6, 7, 8]

def debug():
    """调试
    """

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))