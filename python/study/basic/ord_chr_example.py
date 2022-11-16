# -*- coding: utf-8 -*-
"""
文 件 名: ord_chr_example.py
文件描述: 学习ord和chr函数
作    者: HanKin
创建日期: 2022.10.22
修改日期：2022.10.22

Copyright (c) 2022 HanKin. All rights reserved.
"""


msg = 'www.BAIDU.com.123'
for num in msg:
    if 97 <= ord(num) <= 122: # 小写字母
        upper_num = ord(num)-32 #大小写字母之前差了32
        #chr()函数可以将编码数值转为字符（python没有字符的概念）
        print(chr(upper_num), end='')
    else:
        print(num, end='')  # 不是小写字符，原样输出

print()
print('-' * 50)
print(ord('a'))
print('*' * 50)
print(chr(97), end='')
