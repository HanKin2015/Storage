# -*- coding: utf-8 -*-
"""
文 件 名: deep_shallow_copy.py
文件描述: 在Python中，深拷贝（deep copy）和浅拷贝（shallow copy）是用于复制对象的两种不同方式
备    注: 浅拷贝是创建一个新的对象，该对象与原始对象共享内部对象的引用。换句话说，浅拷贝只复制了对象的引用，而不是对象本身。这意味着如果原始对象中的某个内部对象发生改变，浅拷贝的对象也会受到影响
作    者: HanKin
创建日期: 2023.09.25
修改日期：2023.09.25

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
import time
import copy

def shallow_copy1():
    A = {"name": "zs", "age": "54", "sex": "male"}
    B = A
    print(id(A))
    print(id(B))
    for k, v in A.items():
        if v == "54":
            del B[k]
    print(A)
    print(B)

def shallow_copy2():
    A = {"name": "zs", "age": "54", "sex": "male"}
    B = A.copy()
    print(id(A))
    print(id(B))
    for k, v in A.items():
        if v == "54":
            del B[k]
    print(A)
    print(B)

def shallow_copy3():
    A = {"name": "zs", "age": "54", "sex": "male"}
    B = copy.copy(A)
    print(id(A))
    print(id(B))
    for k, v in A.items():
        if v == "54":
            del B[k]
    print(A)
    print(B)

def deep_copy1():
    A = {"name": "zs", "age": "54", "sex": "male"}
    B = copy.deepcopy(A)
    print(id(A))
    print(id(B))
    for k, v in A.items():
        if v == "54":
            del B[k]
    print(A)
    print(B)

def deep_copy2():
    """
    字典对象没有内置的deepcopy方法
    """
    A = {"name": "zs", "age": "54", "sex": "male"}
    B = A.deepcopy()
    print(id(A))
    print(id(B))
    for k, v in A.items():
        if v == "54":
            del B[k]
    print(A)
    print(B)

def FQA1():
    """
    字典对象中包含了不可变对象，例如数字或字符串。对于不可变对象，浅拷贝会创建一个新的对象，而不是共享原始对象的引用
    """
    old_dict = {'key': 123}

    new_dict = copy.copy(old_dict)

    print(id(old_dict['key']))  # 输出：140722947238800
    print(id(new_dict['key']))  # 输出：140722947238800
    print(id(old_dict))
    print(id(new_dict))

    # 修改原始字典中的值
    old_dict['key'] = 456

    print(old_dict)  # 输出：{'key': 456}
    print(new_dict)  # 输出：{'key': 123}

def FQA2():
    """
    如果字典对象中包含可变对象，例如列表或字典，则浅拷贝会共享原始对象的引用。这意味着如果原始对象中的可变对象发生改变，浅拷贝的对象也会受到影响
    """
    old_dict = {'key': [1, 2, 3]}

    new_dict = copy.copy(old_dict)

    print(id(old_dict['key']))  # 输出：140722947238800
    print(id(new_dict['key']))  # 输出：140722947238800
    print(id(old_dict))
    print(id(new_dict))

    # 修改原始字典中的值
    old_dict['key'][1] = 100

    old_dict['key'] = [2, 3, 4]
    print(old_dict)  # 输出：{'key': [2, 3, 4]}
    print(new_dict)  # 输出：{'key': [1, 2, 3]}

def FQA3():
    """
    浅拷贝和深拷贝在处理嵌套对象时有很大的区别
    """
    # 原始列表对象
    old_list = [[1, 2, 3], [4, 5, 6]]

    # 浅拷贝
    new_list_shallow = copy.copy(old_list)

    # 深拷贝
    new_list_deep = copy.deepcopy(old_list)

    # 修改原始列表中的值
    old_list[0][0] = 9

    print(old_list)  # 输出：[[9, 2, 3], [4, 5, 6]]
    print(new_list_shallow)  # 输出：[[9, 2, 3], [4, 5, 6]]
    print(new_list_deep)  # 输出：[[1, 2, 3], [4, 5, 6]]

def main():
    """主函数
    """

    FQA2()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
