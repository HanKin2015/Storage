# -*- coding: utf-8 -*-
"""
@description:
    生成密码库

@author: hankin
@date  : 2021.06.16

Copyright (c) 2021 HanKin. All rights reserved.
"""

import itertools as its
import string
import time

def createDict(path, repeats, words):
    dict = its.product(words, repeat=repeats) 
    '''这里的words是要迭代的字符串，repeats是生成的密码长度，生成的dict是一个返回元组的迭代器'''
    cnt = 0
    try:
        f = open(path, 'a')
    except Exception as e:
        print(e)
        return 0
        
    for cipher in dict:
        f.write(''.join(cipher) + '\n')
        cnt += 1
    f.close()
    return cnt

def main():
    #numbers = string.digits             # 包含0-9的字符串
    #letters = string.ascii_letters      # 包含a-z和A-Z的字符串
    #lower_letters = string.lowercase    # 包含a-z的字符串
    custom_letters = 'afgnors'   # 自定义字符串
    path = './dict/passwd.txt'          # 存储位置
    length = 7                          # 密码长度范围1~length
    passwd_cnt = 0
    for i in range(7, length+1):
        #createDict(path, i, numbers)
        passwd_cnt += createDict(path, i, custom_letters)
    print("共生成{}个密码".format(passwd_cnt))

if __name__=="__main__":
    start = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

    main()

    end = time.time()
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
    spend_time   = end - start
    spend_hour   = spend_time // 3600
    spend_minute = (spend_time - spend_hour * 3600) // 60
    spend_second = spend_time - spend_hour * 3600 - spend_minute * 60
    print('程序耗时: %d小时%d分%d秒.' % (spend_hour, spend_minute, spend_second))
