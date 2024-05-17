# -*- coding: utf-8 -*-
"""
文 件 名: rand_generate_verification_code.py
文件描述: 实现生成随机十六位验证码的功能
作    者: HanKin
创建日期: 2024.04.11
修改日期：2024.04.11

Copyright (c) 2024 HanKin. All rights reserved.
"""
#样例
#生成验证码
#我们在生活中经常遇到需要输入验证码的时候，一般验证码都是随机生成的、包含多个大写字符、小写字母或数字的随机字符序列。
#要求编写程序，实现生成随机六位验证码的功能
#问题分析:
#(1)验证码共十六位，需生成十六个随机字符;
# (2)每次生成的随机字符需存储到某数据结构之中;
#(3)数据结构应具有可变、有序的特点。
#功能:随机生成十六位验证码
import random #导入随机模块

code_list = [] # 建立空列表
# 控制验证码的位数
for i in range(16):
    #随机生成状态码
    state = random.randint(1, 4)
    if state == 1:
        #随机生成大写字母
        first_kind = random.randint(65, 90)
        random_uppercase = chr(first_kind)
        code_list.append(random_uppercase)#随机生成的一位验证码加入到列表中
    elif state == 2:
        #随机生成小写字母
        second_kinds = random.randint(97, 122)
        random_lowercase =chr(second_kinds)
        code_list.append(random_lowercase)
    elif state == 3:
        #随机生成数字
        third_kinds = random.randint(0, 9)
        code_list.append(str(third_kinds))
    elif state == 4:
        #随机生成特殊字符
        fourth_kinds = random.randint(33, 47)
        random_char = chr(fourth_kinds)
        code_list.append(random_char)
    
#将列表元素连接成字符串
verification_code ="".join(code_list)
print(verification_code)