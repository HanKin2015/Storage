# -*- coding: utf-8 -*-
"""
Created on Fri Sep 11 20:00:14 2020

@author: Administrator
"""

def fun():
	print(12345)
	
file_path = './test.txt'
def write_file(content):
    print('正在写入', file_path)
    
    try:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
    except Exception as ex:
        print('打开文件失败, error=', ex)
