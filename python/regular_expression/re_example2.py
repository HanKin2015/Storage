# -*- coding: utf-8 -*-
"""
文 件 名: re_example2.py
文件描述: 学习正则表达式
作    者: HanKin
创建日期: 2023.09.28
修改日期：2023.09.28

Copyright (c) 2023 HanKin. All rights reserved.
"""

import re
import time

def test():
    """对于字符串"1,*,*;3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    对于字符串"3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    匹配是否存在1,*,*字符串
    """
    
    str1 = "1,*,*;3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    str2 = "3,*,1;3,*,2;a,*,*;d,*,*;f,*,*;11,*,*;12,*,*;dc,*,*;e0,*,*;ef,*,*"
    # 错误的方式
    if "1,*,*" in str1:
        print("str1 exist 1,*,* string")
    # 正确的方式
    if "1,*,*" in str2.split(";"):
        print("str2 exist 1,*,* string")

    # 使用正则
    pattern = r"\b1,*,*\b"
    
    match = re.search(pattern, str1)
    if match:
        print("字符串str1中包含'1,*,*'")
    else:
        print("字符串str1中不包含'1,*,*'")

    match = re.search(pattern, str2)
    if match:
        print("字符串str2中包含'1,*,*'")
    else:
        print("字符串str2中不包含'1,*,*'")

def main():
    test()

if __name__ == '__main__':
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
 