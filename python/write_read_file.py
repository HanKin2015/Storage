# -*- coding: utf-8 -*-
"""
Created on Tue Sep  1 20:33:14 2020

@author: Administrator
"""

file_path = "./msg_between_extranet_and_intranet.txt"

def read_file():
    print('正在读取', file_path)
    content_list = []
    
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content_list = f.readlines() 
    except Exception as ex:
        print('打开文件失败, error=', ex)
    
    print(type(content_list))
    
    content = ''
    for elem in content_list:
        content = content + elem
    print(content)

def write_file(content):
    print('正在写入', file_path)
    
    try:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
    except Exception as ex:
        print('打开文件失败, error=', ex)

if __name__ == '__main__':
    read_file()
    write_file('hjj\nds')
    read_file()
    
    
    
    
    
    