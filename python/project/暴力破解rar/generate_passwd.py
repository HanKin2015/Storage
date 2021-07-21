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

def createDict(path, repeats, words):
	dict = its.product(words, repeat=repeats) 
	'''这里的words是要迭代的字符串，repeats是生成的密码长度，生成的dict是一个返回元组的迭代器'''
	f = open(path,'a')
	for cipher in dict:
		f.write(''.join(cipher) + '\n')
	f.close()

def main():
	numbers = string.digits # 包含0-9的字符串
	path = './passwd.txt'   # 存储位置
	length = 3              # 密码长度范围1~length
	for i in range(1, length+1):
		createDict(path, i, numbers)

if __name__=="__main__":
	main()
