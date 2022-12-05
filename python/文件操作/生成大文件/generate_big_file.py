# -*- coding: utf-8 -*-
"""
文 件 名: generate_big_file.py
文件描述: 快速生成大文件
作    者: HanKin
创建日期: 2022.04.25
修改日期：2022.04.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

import os
import time
import datetime
import sys
import random

def generate_file1(n):
    # 先使用seek函数为打开的文件偏移一个很大的空间，然后写入数据即可
    '''
    seek() 方法用于移动文件读取指针到指定位置。
    语法
    seek() 方法语法如下：
    fileObject.seek(offset[, whence])
    参数
    offset -- 开始的偏移量，也就是代表需要移动偏移的字节数
    whence：可选，默认值为 0。给offset参数一个定义，表示要从哪个位置开始偏移；0代表从文件开头开始算起，1代表从当前位置开始算起，2代表从文件末尾算起。
    '''
    local_time = time.strftime("%Y%m%d%H%M%S", time.localtime())
    file_name = 'M:\\{}.txt'.format(str(local_time))
    big_file= open(file_name, 'w', encoding='utf-8')
    big_file.seek(1024*1024*n)
    random_content = str(round(random.uniform(0, 1000), 1))
    big_file.write(random_content)
    big_file.close()

def generate_file2():
    nlines = 100000
    col = 50
    
    f = open('input.txt', 'w')
    for i in range(nlines):
        nums = [str(round(random.uniform(0, 1000), 1)) for j in range(col)]
        f.write(' '.join(nums))
        f.write('\n')
    f.close()

def main():
    begin_time = time.time()
    generate_file1(200)
    #generate_file2()
    end_time = time.time()
    copy_time = round(end_time - begin_time, 3)
    print('花费 {} s'.format(copy_time))

if __name__ == '__main__':
    main()