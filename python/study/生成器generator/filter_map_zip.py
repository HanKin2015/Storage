# -*- coding: utf-8 -*-
"""
文 件 名: filter_map_zip.py
文件描述: 学习filter、map和zip函数
作    者: HanKin
创建日期: 2022.08.24
修改日期：2022.08.24

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import sys
import math
import random

def is_sqr(x):
    return math.sqrt(x) % 1 == 0

def is_odd(n):
    return n % 2 == 1
    
def filter_example():
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))

    tmplist = filter(is_odd, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    newlist = list(tmplist)
    print('过滤出列表中的所有奇数: {}'.format(newlist))
    
    tmplist = filter(is_sqr, range(1, 101))
    newlist = list(tmplist)
    print('过滤出1~100中平方根是整数的数: {}'.format(newlist))

def square(x) :            # 计算平方数
    return x ** 2

def format_name(s):
    ss=s[0:1].upper()+s[1:].lower();
    return ss;
    
def map_example():
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    print(list(map(square, [1,2,3,4,5])))   # 计算列表各个元素的平方
    print(list(map(lambda x: x ** 2, [1, 2, 3, 4, 5])))  # 使用 lambda 匿名函数
    # 提供了两个列表，对相同位置的列表数据进行相加
    print(list(map(lambda x, y: x + y, [1, 3, 5, 7, 9], [2, 4, 6, 8, 10])))

    # 只执行了 4 个元素的的计算
    listx = [1, 2, 3, 4, 5, 6, 7]       # 7 个元素
    listy = [2, 3, 4, 5, 6, 7]         # 6 个元素 
    listz = [100, 100, 100, 100]     # 4 个元素
    list_result = map(lambda x,y,z : x**2 + y + z, listx, listy, listz)
    print(list(list_result))
    
    name_list = {'tony', 'cHarLIE', 'rachAEl'}
    print(list(map(format_name, name_list)))
    print(type(name_list))

    res1 = map(lambda n: n > 5, range(10))
    lt1 = list(res1)
    print(lt1)
    res2 = filter(lambda n: n > 5, range(10))
    lt = list(res2)
    print(lt) 

def zip_example():
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    a = [1,2,3]
    b = [4,5,6]
    c = [4,5,6,7,8]
    zipped = zip(a,b)     # 返回一个对象
    print(zipped)
    #print(list(zipped))   # list() 转换为列表
    print(zipped, type(zipped))
    print(list(zip(a,c)))          # 元素个数与最短的列表一致
    time.sleep(1)
    a1, a2 = zip(*zipped)          # 与 zip 相反，zip(*) 可理解为解压，返回二维矩阵式
    a1, a2 = zip(*zip(a,b))
    print(type(zip(a,b)))
    print(type(zipped))
    print(list(a1))
    print(list(a2))
    print(type(a1))

def zip_in_ml():
    """
    机器学习模型训练中，经常需要打乱数据集，用 zip() 函数可以实现
    """
    
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    X = [1, 2, 3, 4, 5, 6]
    y = [0, 1, 0, 0, 1, 1]
    zipped_data = list(zip(X, y))
    
    # 将样本和标签一 一对应组合起来,并转换成list类型方便后续打乱操作
    random.shuffle(zipped_data)
    
    # 使用random模块中的shuffle函数打乱列表，原地操作，没有返回值
    new_zipped_data = list(map(list, zip(*zipped_data)))
    
    # zip(*)反向解压，map()逐项转换类型，list()做最后转换
    new_X, new_y = new_zipped_data[0], new_zipped_data[1]
    
    # 返回打乱后的新数据
    print('X: {}\ny: {}'.format(X, y))
    print('new_X: {}\nnew_y: {}'.format(new_X, new_y))

def zip_in_ml_generate_data():
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    X = [1, 2, 3, 4, 5, 6]
    y = [0, 1, 0, 0, 1, 1]
    zipped_data = list(zip(X, y))
    print(zipped_data)
    
    lst = []
    n = 10
    for i in range(1, n+1): # n为数据集的个数
        lst.append(i)
    print(lst)

    x = [11, 22, 33, 44]
    k = enumerate(x, start = 1) # x为数据集
    print(k)
    zipped_data = list(enumerate(x, start = 1))
    print(zipped_data)

def zip_T():
    """
    python 中二维数组的转置
    
    [(1, 2), (3, 4), (5, 6), (7, 8), (9, 10)]
    [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10]]  这是数组
    """
    
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    array = [[1, 4], [2, 5], [3, 6]]
    print(map(list, zip(*array)))

    print(list(zip([1, 3, 5, 7, 9], [2, 4, 6, 8, 10])))
    print(list(map(lambda x,y : [x,y], [1,3,5,7,9], [2,4,6,8,10])))

def main():
    filter_example()
    map_example()
    zip_example()
    zip_in_ml()
    zip_in_ml_generate_data()
    zip_T()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
