# -*- coding: utf-8 -*-
"""
文 件 名: num2chinese.py
文件描述: 将数字金额转为中文大写金额
作    者: HanKin
创建日期: 2023.11.06
修改日期：2023.11.06

Copyright (c) 2023 HanKin. All rights reserved.
"""
import num2chinese

def num2chinese2(num):
    """
    将数字金额转为中文大写金额
    :param num: 数字金额
    :return: 中文大写金额
    """
    chinese_num = ['零', '壹', '贰', '叁', '肆', '伍', '陆', '柒', '捌', '玖']
    chinese_unit = ['', '拾', '佰', '仟', '万', '亿']
    num_str = str(num)
    num_len = len(num_str)
    print("num_str = {}, num_len = {}".format(num_str, num_len))
    
    chinese_str = ''
    zero_flag = False
    for i in range(num_len):
        j = int(num_str[i])
        if j == 0:
            zero_flag = True
        else:
            if zero_flag:
                chinese_str += chinese_num[0]
                zero_flag = False
            print("j = {}, i = {}".format(j, i))
            chinese_str += chinese_num[j] + chinese_unit[num_len - i - 1]
    if zero_flag:
        chinese_str += zero_num[0]
    return chinese_str

if __name__ == '__main__':
    print(num2chinese2(12345))
    number = 2274587.84
    #chinese = num2chinese(number)
    chinese = num2chinese.normalizer.normalize(str(number))
    print(chinese + "元")
    