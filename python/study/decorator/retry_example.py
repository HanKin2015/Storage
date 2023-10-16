# -*- coding: utf-8 -*-
"""
文 件 名: retry_example.py
文件描述: retry装饰器
作    者: HanKin
创建日期: 2023.10.12
修改日期：2023.10.12

Copyright (c) 2023 HanKin. All rights reserved.
"""

from retrying import retry
import time

number = -1

@retry(stop_max_attempt_number=5, wait_fixed=2000)
def my_func():
    """
    ******** starting ********
    division by zero
    process spend 2.003 s.
    """
    try:
        global number
        number += 1
        result = 100 / number
    except Exception as err:
        print(err)
    return result

def main():
    """主函数
    """

    my_func()

if __name__ == '__main__':
    """程序入口
    """

    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))