# -*- coding: utf-8 -*-
"""
文 件 名: zip_example.py
文件描述: time库中的sleep函数是否支持500毫秒睡眠
作    者: HanKin
创建日期: 2023.10.17
修改日期：2023.10.17

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import os
import sys

def main():
    """主函数
    """

    # 答案是支持的
    time.sleep(0.5)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))