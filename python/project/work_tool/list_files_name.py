# -*- coding: utf-8 -*-
"""
文 件 名: list_files_name.py
文件描述: 列出文件名
备    注: 
作    者: HanKin
创建日期: 2024.11.20
修改日期：2024.11.20

Copyright (c) 2024 HanKin. All rights reserved.
"""
import os
import time
import re

def list_specified_suffix_files_recursion(dir_path, suffix_list):
    """
    列出指定后缀的文件（会递归）
    """
    problem_numbers = []
    for root, dirs, files in os.walk(dir_path, topdown=False):
        for file in files:
            suffix = file.split(".")[-1]
            if suffix in suffix_list:
                # 正则表达式模式，匹配以 'Q' 开头，后跟一串数字的字符串
                pattern = r'Q\d{13}'
                match = re.search(pattern, file)
                if match:
                    #print("problem number is {}".format(match.group(0)))
                    print("current suffix[{}] file: {}".format(suffix, file))
                    problem_numbers.append(match.group(0))
                    file_path = os.path.join(root, file)
    print("there are {} files with {} suffix and problem number".format(len(problem_numbers), suffix_list))
    print(problem_numbers)

def list_specified_suffix_files(dir_path, suffix_list):
    """
    列出指定后缀的文件
    """
    count = 0
    for file in os.listdir(dir_path):
        suffix = file.split(".")[-1]
        if suffix in suffix_list:
            print("current suffix[{}] file: {}".format(suffix, file))
            count += 1
    print("there are {} files with {} suffix".format(count, suffix_list))


def main():
    """主函数
    """

def debug():
    """调试
    """
    directory_path = r'D:\Users\Administrator\Desktop'
    list_specified_suffix_files_recursion(directory_path, ['docx', 'doc'])

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    #main()
    debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))