# -*- coding: utf-8 -*-
"""
文 件 名: get_demo_info.py
文件描述: 获取当前代码的文件名，行号，函数名以及时间
作    者: HanKin
创建日期: 2022.08.22
修改日期：2022.08.22

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
import time
import os

def main(): 
    print('全路径文件: {}'.format(__file__))
    print('文件名: {}'.format(os.path.basename(__file__)))
    print('函数名: {} (不正确)'.format(__name__))
    print('行  号: {}'.format(sys._getframe().f_lineno))
    print('函数名: {}'.format(sys._getframe().f_code.co_name))
    print('函数名: {}'.format(sys._getframe(0).f_code.co_name))
    # 调用该函数的函数的名字，如果没有被调用，则返回<module>，貌似call stack的栈低
    print('函数名: {}'.format(sys._getframe(1).f_code.co_name))
    # 当前文件名，可以通过__file__获得
    print('文件名: {}'.format(sys._getframe().f_code.co_filename))
    print(time.strftime("%Y-%m-%d %H:%M:%S"))

def debug():
    main()

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    #main()
    debug()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))

"""
******** starting ********
全路径文件: get_demo_info.py
文件名: get_demo_info.py
函数名: __main__ (不正确)
行  号: 20
函数名: main
函数名: main
函数名: debug
文件名: get_demo_info.py
2022-08-22 16:49:40
process spend 0.005 s.
"""