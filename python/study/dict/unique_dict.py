# -*- coding: utf-8 -*-
"""
文 件 名: unique_dict.py
文件描述: 字典列表去重
作    者: HanKin
创建日期: 2023.09.28
修改日期：2023.09.28

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

def main():
    """主函数
    """
    
    # 使用列表推导式（list comprehension）和集合（set）来去重
    my_list = [{"a": 1, "b": 2}, {"a": 1, "b": 2}, {"a": 3, "b": 4}]
    unique_list = [dict(t) for t in set([tuple(sorted(d.items())) for d in my_list])]
    print(unique_list)

    # 使用列表推导式和字典推导式（dictionary comprehension）来去重
    my_list = [{"a": 1, "b": 2}, {"a": 1, "b": 2}, {"a": 3, "b": 4}]
    unique_list = [dict(t) for t in {tuple(d.items()) for d in my_list}]
    print(unique_list)

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