# -*- coding: utf-8 -*-
"""
文 件 名: nest_exception.py
文件描述: 异常
作    者: HanKin
创建日期: 2024.07.18
修改日期：2024.07.18

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
import traceback

def nest_exception():
    """
    嵌套没有问题，是项目代码有问题
    
    ******** starting ********
    外面这层进入
    Traceback (most recent call last):
      File "nest_exception.py", line 21, in nest_exception
        result = 100 / 0
    ZeroDivisionError: division by zero
    打印异常: Traceback (most recent call last):
      File "nest_exception.py", line 21, in nest_exception
        result = 100 / 0
    ZeroDivisionError: division by zero

    process spend 0.012 s.
    """
    try:
        print("外面这层进入")
        try:
            result = 100 / 0
        except Exception as e:
            traceback.print_exc()
            print("打印异常: {}".format(traceback.format_exc()))
    except Exception as e:
        print("外面这层抛出异常")

def main():
    """主函数
    """

    nest_exception()

if __name__ == '__main__':
    """程序入口
    """

    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))