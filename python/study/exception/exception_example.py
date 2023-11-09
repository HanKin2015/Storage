# -*- coding: utf-8 -*-
"""
文 件 名: exception_example.py
文件描述: 异常
作    者: HanKin
创建日期: 2023.10.12
修改日期：2023.10.12

Copyright (c) 2023 HanKin. All rights reserved.
"""
import time
import traceback

def traceback_example1():
    """
    打印异常
    """
    try:
        result = 100 / 0
    except Exception as e:
        traceback.print_exc()

def traceback_example2():
    """
    返回异常字符串，不打印
    """
    try:
        result = 100 / 0
    except Exception as e:
        traceback.format_exc()

def exception_example():
    """
    返回异常错误，但是无法追踪到代码中具体的位置
    """
    try:
        result = 100 / 0
    except Exception as e:
        print(e)

def raise_example():
    """
    主动抛出异常
    """
    try:
        raise Exception("有问题")
    except Exception as e:
        print(e)

def main():
    """主函数
    """

    traceback_example1()
    traceback_example2()
    exception_example()
    raise_example()

if __name__ == '__main__':
    """程序入口
    """

    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))