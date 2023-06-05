# -*- coding: utf-8 -*-
"""
文 件 名: dict_zip_example1.py
文件描述: 通过for循环，循环d列表，实现形成一个新字典
作    者: HanKin
创建日期: 2023.06.02
修改日期：2023.06.02

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time

def method1():
    """使用zip()函数将d列表和a、b、c列表分别打包成元组，然后再通过字典推导式生成字典e
    """
    
    a = [1, 2, 3]
    b = [4, 5, 6]
    c = [7, 8, 9]
    d = ["a", "b", "c"]

    # 遍历d列表，生成字典e
    e = {key: value for key, value in zip(d, [a, b, c])}
    print(e)

def method2():
    """用globals()解决
    存在作用域问题，详情见D:\Github\GitBook\gitbook\Python\python_study.md
    在使用global修饰后变量是不可以直接赋值的，直接赋值会报错
    """
    
    global a
    a = [1, 2, 3]
    global b
    b = [4, 5, 6]
    global c
    c = [7, 8, 9]
    d = ["a", "b", "c"]
    
    #print(globals())
    e = {i:globals()[i] for i in d}
    print(e)

def main():
    """主函数
    """
    
    method1()
    method2()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    
    # 必须要在__main__函数中定义，这样才会在globals()里面去
    a = [1, 2, 3]
    b = [4, 5, 6]
    c = [7, 8, 9]
    d = ["a", "b", "c"]
    
    #print(globals())
    e = {i:globals()[i] for i in d}
    print(e)

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))