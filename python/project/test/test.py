# -*- coding: utf-8 -*-
"""
Created on Wed Sep  9 17:44:48 2020

@author: Administrator
"""


a = [1, 2, 3, 4]
print(a)
print(zip(a))

b = 'hello'
c = 'hell'
if b is not c:
	print('yes')
else:
	print('no')

import os
path = 'D:/Downloads/'
for root,dirs,files in os.walk(path):
	for name in files:
		print(os.path.join(root,name))
		print(root)

path = 'D:/Github/Storage/python'
print(path.rfind('/'))
print(path[17+1:])

'''		
import md5
src = 'this is a md5 test.'
m1 = md5.new()
m1.update(src)
print(m1.hexdigest())
'''
	

str = "this string example....wow!!!";
print(str.startswith('str', 4, 10))
print(str.startswith('is', 3, 8))
print(str.startswith('is', 2, 8))
print(str.startswith('this', 2, 4))










	