# -*- coding: utf-8 -*-
"""
文 件 名: remove_eference_dimension.py
文件描述: 移除引用标注
作    者: HanKin
创建日期: 2023.01.04
修改日期：2023.01.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

class MyClass:
    
    def __init__(self):
        self.x = 12
        self.y = 14
    
    @staticmethod
    def hello():
        print('hello')

    def world():
        print('world')

    def func(self):
        print(self.x)

def main():
    """主函数
    """

    MyClass.hello()
    MyClass.world()
    MyClass().func()

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