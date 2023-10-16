# -*- coding: utf-8 -*-
"""
文 件 名: dict_example.py
文件描述: 学习字典数据结构
作    者: HanKin
创建日期: 2023.09.19
修改日期：2023.09.19

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

def main():
    """主函数
    """

    # 字典判空
    my_dict = {}
    if not my_dict:
        print("字典为空")
    else:
        print("字典不为空")

    # 判断一个变量是否为字典类型
    my_dict = {'key': 'value'}
    if isinstance(my_dict, dict):
        print('my_dict是字典类型')
    else:
        print('my_dict不是字典类型')

    # 字典判断是否存在某个键
    my_dict = {'name': 'Alice', 'age': 25, 'city': 'Beijing'}
    if 'name' in my_dict:
        print("键 'name' 存在于字典中")
    else:
        print("键 'name' 不存在于字典中")
    if 'gender' in my_dict:
        print("键 'gender' 存在于字典中")
    else:
        print("键 'gender' 不存在于字典中")

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