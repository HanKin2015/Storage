# -*- coding: utf-8 -*-
"""
文 件 名: import_package_from_differrent_position.py
文件描述: 不同的地方导入包是否存在问题
作    者: HanKin
创建日期: 2024.05.23
修改日期：2024.05.23

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time

class Test():
    def __init__(self):
        super().__init__()
    
    def callback(self):
        x = 1
        y = 3
        print(np.max([x, y]))

def func():
    x = 1
    y = 3
    print(np.max([x, y]))

def main():
    """主函数
    """
    
    # 把这行放在这里后存在异常问题，但是放在__main__函数和全局就是正常的
    import numpy as np
    x = 1
    y = 3
    print(np.max([x, y]))
    
    func()
    
    obj = Test()
    obj.callback()

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


