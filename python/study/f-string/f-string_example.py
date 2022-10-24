# -*- coding: utf-8 -*-
"""
文 件 名: f-string_example.py
文件描述: Python新式格式化输出：f-string
参    考: https://www.bilibili.com/read/cv15716944
作    者: HanKin
创建日期: 2022.10.24
修改日期：2022.10.24

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import math

def basic_usage():
    """f-string用大括{ }表示被替换字段，其中直接填入替换内容即可
    """
    
    name = "Zhang San"
    age = 23
    price = 12.5
    print(f"Hello, my name is {name}, my age is {age}, I have {price}$")

def expression_evaluation_and_function_call():
    """
    """
    
    # 1、 f-string的大括号{ }可以填入表达式或调用函数，Python会求出其结果并填入返回的字符串内
    name = "Zhang San"
    print(f"my name is {name.lower()}, I have {2+5*2} apples. Π的值为{math.pi}")
    
    # 2、f-string中使用lambda匿名函数：可以做复杂的数值计算
    aa = 123.456
    print(f"{(lambda x:x*5-2)(aa):.2f}")
    bb = 8
    cc = 2
    # 说明：注意语法格式的写法，第一个小括号表示的是lambda表达式，第二个小括号表示给lambda表达式传入参数
    print(f"{(lambda x,y:x+y)(bb,cc)}")

def main():
    basic_usage()
    expression_evaluation_and_function_call()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
