# -*- coding: utf-8 -*-
"""
Created on Mon Sep 21 11:24:15 2020

@author: hankin
"""

str_exam = 'he jk he'

if 'jk' in str_exam:
    print('yes')
else:
    print('no')
    
print(str_exam.find('he'))
print(str_exam.rfind('he'))
print(str_exam.index('he'))
print(str_exam.rindex('he'))
print(str_exam.count('he'))

#index()/rindex()方法跟find()/rfind()方法相似，只不过在找不到子字符串的时候会报一个ValueError的异常，而不是-1。
try:
    print(str_exam.index('her'))
except Exception as ex:
    print(ex)
print(str_exam.find('her'))

结果：
yes
0
6
0
6
2
substring not found
-1