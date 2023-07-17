# -*- coding: utf-8 -*-
"""
文 件 名: delete_line_end_whitespace.py
文件描述: 删除行末空白字符
作    者: HanKin
创建日期: 2023.07.17
修改日期：2023.07.17

Copyright (c) 2023 HanKin. All rights reserved.
"""

import os
import stat
import time
  
if __name__ == '__main__':
    """程序入口
    """
    
    # 文件路径，所有方法都会读取到换行符
    INPUT_FILE_PATH  = './sf_redirect.out'
    OUTPUT_FILE_PATH = './sf_redirect.out1'
    
    # 1、直接打开就读，速度最快最简洁
    with open(INPUT_FILE_PATH, 'r', encoding='utf-8') as fr:
        with open(OUTPUT_FILE_PATH, 'w', encoding='utf-8') as fw:
            change_line_count = 0
            for i, line in enumerate(fr):
                line_len = len(line)
                # 一行的长度包含了换行符在内
                #print(line_len)
                # 一行内容从下标0开始，基本上都是右边值取不到
                for j in range(line_len-1, -1, -1):
                    #print(line[j])
                    pass
                
                # 找到行末不为0的位置，起点跳过换行符
                not_space_pos = -1
                for j in range(line_len-2, -1, -1):
                    if line[j] != ' ':
                        not_space_pos = j
                        break
                    
                if not_space_pos == -1: # 两种情况，一是整行全是空格，二是空行
                    fw.write(line[-1])
                    if line_len != 1:
                        print('line: {}'.format(i+1))
                        change_line_count += 1
                else:
                    fw.write(line[:not_space_pos+1])
                    fw.write(line[-1])
                    if not_space_pos != line_len-2:
                        print('line: {}'.format(i+1))
                        change_line_count += 1
            print('there are {} lines which are changed'.format(change_line_count))