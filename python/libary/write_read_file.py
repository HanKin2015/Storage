# -*- coding: utf-8 -*-
"""
Created on Tue Sep  1 20:33:14 2020

@author: Administrator
"""

from datetime import datetime
import sys

file_path = "D:/Github/Storage/python/libary/读写文件.txt"

def get_head_info():
    try:
        raise Exception
    except:
        f = sys.exc_info()[2].tb_frame.f_back
    return '%s, %s, %s, %s, ' % (str(datetime.now()), f.f_code.co_filename, f.f_code.co_name, str(f.f_lineno))

def read_file_by_lines():
    '''
    通过readlines一次性读取整个文件；自动将文件内容分解成一个行的列表。
    '''
    print('正在读取', file_path)
    content_list = []
    
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            print('是否是一次性全部读取?')
            content_list = f.readlines() 
    except Exception as ex:
        print('打开文件失败, error=', ex)
    
    print(type(content_list))
    
    content = ''
    for elem in content_list:
        content = content + elem
    print(content)
    
def read_file_by_read():
    '''
    通过read一次性读取整个文件内容存储到一个字符串中。
    '''
    
    print('正在读取', file_path)
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            print('是否是一次性全部读取?')
            content = f.read() 
    except Exception as ex:
        print('打开文件失败, error=', ex)
    
    print(type(content))
    print(content)
    print(get_head_info())

def write_file(content):
    print('正在写入', file_path)
    
    try:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
    except Exception as ex:
        print('打开文件失败, error=', ex)

if __name__ == '__main__':
    read_file_by_lines()
    write_file('''
    床前明月光,
疑是地上霜.
    举头望明月,
    低头思故乡.
    ''')
    read_file_by_lines()
    read_file_by_read()
    