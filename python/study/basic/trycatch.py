# -*- coding: utf-8 -*-
"""
文 件 名: trycatch.py
文件描述: 异常处理
作    者: HanKin
创建日期: 2022.04.26
修改日期：2022.04.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys

def try_except_exam1():
    '''多个except子句
    '''
    
    try:
        digit = int(input('输入一个非0的数字: '))
        ret = 10 / digit
    except ValueError as err:
        print('err: {}'.format(err))
    except ZeroDivisionError as err:
        print('err: {}'.format(err))
        
def try_except_exam2():
    '''一个except块捕捉多个异常
    '''
    
    try:
        digit = int(input('输入一个非0的数字: '))
        ret = 10 / digit
    except (ValueError, ZeroDivisionError) as err:
        print('err: {}'.format(err))

def try_except_exam3():
    '''空except：捕捉所有异常
    '''
    
    try:
        digit = int(input('输入一个非0的数字: '))
        ret = 10 / digit
    except Exception as err:
        print('err: {}'.format(err))

def try_except_exam4():
    '''空except：捕捉所有异常
    '''
    
    try:
        digit = int(input('输入一个非0的数字: '))
        ret = 10 / digit
    except:
        print('err: {}'.format(Exception))
        
def try_except_exam5():
    '''如果try块中没有异常，则else语句被执行
    '''
    
    try:
        digit = int(input('输入一个非0的数字: '))
        ret = 10 / digit
    except Exception as err:
        print('err: {}'.format(err))
    else:
        print('no exception')
        
def try_except_exam6():
    '''finally语句可以用在try语句中，无论是否发生异常，finally子句中的语句块都要被执行
    '''
    
    try:
        digit = int(input('输入一个非0的数字: '))
        ret = 10 / digit
        return 0
    except Exception as err:
        print('err: {}'.format(err))
        return -1
    else:
        print('no exception')
        return -2
    finally:
        print('It is finally clause')
        return -3

def main():
    ret = try_except_exam6()
    print(ret)

if __name__ == '__main__':
    main()