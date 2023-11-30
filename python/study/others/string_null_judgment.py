# -*- coding: utf-8 -*-
"""
文 件 名: string_null_judgment.py
文件描述: 多个字符串判空
作    者: HanKin
创建日期: 2023.11.30
修改日期：2023.11.30

Copyright (c) 2023 HanKin. All rights reserved.
"""
import time

"""
(base) D:\Users\User\Desktop>python k.py
******** starting ********
a is null
d is not null
there is at least one null here
all are not null
process spend 0.004 s.
"""
def main():
    """主函数
    """
    a = ""
    b = ""
    c = ""
    d = "1"
    e = "2"
    f = "3"
    if a:
        print("a is not null")
    else:
        print("a is null")
    if d:
        print("d is not null")
    else:
        print("d is null")
    if all([a, b, c, d, e, f]):
        print("all are not null")
    else:
        print("there is at least one null here")
    if all([d, e, f]):
        print("all are not null")
    else:
        print("there is at least one null here")

if __name__ == '__main__':
    """程序入口
    """

    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))