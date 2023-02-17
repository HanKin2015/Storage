# -*- coding: utf-8 -*-
"""
文 件 名: regular_expressions_research.py
文件描述: 正则表达式研究
作    者: HanKin
创建日期: 2023.02.15
修改日期：2023.02.15

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import re

def main():
    """主函数
    + :     1次或多次
    []：    指定范围内的的任意单个字符
    * ：    任意次数 0次 1次或多次
    ? ：    0次或1次
    """
    
    line = '消痛[13]贴膏[2]说明[1-3]书'
    pat = re.compile(r"(\[[0-9]+-?[0-9]*\])")
    ret = pat.findall(line)
    if len(ret):
        print(ret)
        line = pat.sub('', line)
    print(line)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))