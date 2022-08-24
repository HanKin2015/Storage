# -*- coding: utf-8 -*-
"""
文 件 名: amazing_zip_error.py
文件描述: 很奇怪的一个zip函数错误
作    者: HanKin
创建日期: 2022.08.23
修改日期：2022.08.23

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
import time

#print(3*None)

def factorial(n):
    """
    计算阶乘
    """
    
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    if n != 1:
        print('n = {}'.format(n))
        n = n * factorial(n - 1)
        print('n = {}'.format(n))
    else:
        return n

def correct_factorial(n):
    """
    计算阶乘
    """
    
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    print('argument n = {}'.format(n))
    
    if n > 1:
        print('n = {}'.format(n))
        n = n * correct_factorial(n - 1)
        print('n = {}'.format(n))
    
    return n

def amazing_zip_error():
    """
    怎么也想不清楚：ValueError: not enough values to unpack (expected 2, got 0)
    注释掉print(list(zipped))就能正常执行
    
    终于明白真相：
    <zip object at 0x7fa5ee7f0948>
    [(1, 4), (2, 5), (3, 6)]
    []
    <zip object at 0x7fa5ee7f0948>
    """

    a = [1,2,3]
    b = [4,5,6]
    zipped = zip(a, b)      # 捆绑
    print(zipped)           # 输出对象的地址
    print(list(zipped))     # 转换成list输出
    print(list(zipped))
    print(zipped)
    a1, a2 = zip(*zipped)   #解绑

def amazing_map_error():
    """
    使用python2执行会报错：TypeError: unsupported operand type(s) for +: 'int' and 'NoneType'
    """

    # 只执行了 4 个元素的的计算
    listx = [1, 2, 3, 4, 5, 6, 7]    # 7 个元素
    listy = [2, 3, 4, 5, 6, 7]       # 6 个元素 
    listz = [100, 100, 100, 100]     # 4 个元素
    list_result = map(lambda x,y,z : x**2 + y + z, listx, listy, listz)
    print(list(list_result))

def other_error():
    """
    字典推导式：字母大小写合并
    
    不设置0默认值的话会报错：TypeError: unsupported operand type(s) for +: 'int' and 'NoneType'
    """
 
    case = {'a': 10, 'b': 34, 'A': 7, 'z': 3}
    
    case_frequency = {
        k.lower(): case.get(k.lower(), 0) + case.get(k.upper(), 0)
        for k in case.keys()
    }
    print(case_frequency)   # Output: {'a': 17, 'b': 34, 'z': 3}

def main():
    #print(factorial(3))
    #print(correct_factorial(3))
    other_error()
    amazing_zip_error()
    #amazing_map_error()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))