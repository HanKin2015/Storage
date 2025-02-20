# -*- coding: utf-8 -*-
"""
文 件 名: helloworld.py
文件描述: 垫脚石
作    者: HanKin
创建日期: 2021.03.26
修改日期：2023.10.16

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

def func1():
    global x    # 没有这行，那么func2函数就会报NameError: name 'x' is not defined
    x = 100     # 这一句必须要存在，否则还是会报NameError: name 'x' is not defined
    print(x)
    
def func2():
    print(x)

def main():
    """主函数
    """

    func1()
    func2()

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