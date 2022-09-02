# -*- coding: utf-8 -*-
"""
文 件 名: replace_map_filter.py
文件描述: 用生成器表达式来改写数据量较大的列表推导
作    者: HanKin
创建日期: 2022.08.22
修改日期：2022.08.22

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import sys

def test1():
    """
    列表推导（list commprehension）：根据一份列表来制作另外一份列表
    """
    
    print('-------- {}[{}] --------'.format(sys._getframe().f_code.co_name, sys._getframe().f_lineno))
    
    # 用列表每个元素平方值构建另一份列表
    a = [1, 2, 3, 4, 5, 6, 7, 8]
    
    # 列表推导写法
    squares = [x ** 2 for x in a]
    print(squares)
    # map写法
    squares = map(lambda x: x ** 2, a)
    print(list(squares))

    # 条件输出
    # 列表推导输出偶数
    squares = [x for x in a if x%2 == 0]
    print(squares)
    
    # map辅以filter输出偶数
    even = map(lambda x: x, filter(lambda x: x % 2 == 0, a))
    print(even)
    print(list(even))
    even = filter(lambda x: x % 2 == 0, a)
    print(list(even))
    even = map(lambda x: x % 2 == 0, a)
    print(list(even))

def test2():
    """
    字典与集也有类似的推导机制，编写算法时，可以通过这些推导机制来创建衍生的数据结构。
    """
    
    chile_ranks = {'ghost': 1, 'god': 2, 'man': 3}
    rank_dict = {rank: name for name,rank in chile_ranks.items()}
    chile_len_set = {len(name) for name in rank_dict.values()}
    print(type(chile_ranks), chile_ranks.items())
    print(type(rank_dict), rank_dict.values())
    print(rank_dict)
    print(chile_len_set)

    #元组与dict互转
    #tuple = dict.items()
    #dict = tuple.values
    print(type(chile_ranks.items()))
    print(type(rank_dict.values()))

def test3():
    """
    zip可以将两个或者多个迭代器封装成一个生成器
    场景说明：需要平行对两个列表进行操作时
    """

    names = ['alice', 'bob', 'cendy']
    letters = [len(n) for n in names]

    longest_name = None
    max_letters = 0

    for name, count in zip(names, letters):
        if count > max_letters:
            longest_name = name
            max_letters = count
    print(longest_name)

def test4():
    """
    尽量用enumerate取代range
    """

    list = [5, 4, 7, 8, 9]
    # range写法
    for i in range(len(list)):
        value = list[i]
        index = i
    # enumerate写法
    for i, value in enumerate(list):
        print('%d: %s' % (i + 1, value))

def main():
    test1()
    test2()
    test3()
    test4()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))