# -*- coding: utf-8 -*-
"""
文 件 名: round_example.py
文件描述: 学习round函数
作    者: HanKin
创建日期: 2022.07.18
修改日期：2022.07.18

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
from decimal import *

def main():
    # 四舍六入规则（a=5.21 b=5.22）
    a=round(5.215,2)
    b=round(5.225,2)
    print('a={0} b={1}'.format(a,b))

    # 五成双规则（a=5.23 b=5.22）
    a=round(5.2254,2)
    b=round(5.2153,2)
    print('a={0} b={1}'.format(a,b))

    # Decimal函数使用（5.21 5.22 5.25 5.26 5.29）
    a1=Decimal(5.215).quantize(Decimal('0.00'))
    a2=Decimal(5.225).quantize(Decimal('0.00'))
    a3=Decimal(5.245).quantize(Decimal('0.00'))
    a4=Decimal(5.265).quantize(Decimal('0.00'))
    a5=Decimal(5.285).quantize(Decimal('0.00'))
    print(a1,a2,a3,a4,a5)

    # 使用字符串形式变成奇进偶舍规则了（5.22 5.22 5.24 5.28 5.29）
    a1 = Decimal('5.215').quantize(Decimal('0.00'))
    a2 = Decimal('5.225').quantize(Decimal('0.00'))
    a3 = Decimal('5.245').quantize(Decimal('0.00'))
    a4 = Decimal('5.275').quantize(Decimal('0.00'))
    a5 = Decimal('5.2851').quantize(Decimal('0.00'))
    print(a1, a2, a3, a4, a5)
    
    # rounding=ROUND_HALF_UP 可以理解为到半向上取整，结合字符串参数Decimal()可以实现四舍五入（5.22 5.23 5.25）
    a1 = Decimal('5.215').quantize(Decimal('0.00'), rounding=ROUND_HALF_UP)
    a2 = Decimal('5.225').quantize(Decimal('0.00'), rounding=ROUND_HALF_UP)
    a3 = Decimal('5.245').quantize(Decimal('0.00'), rounding=ROUND_HALF_UP)
    print(a1, a2, a3)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))