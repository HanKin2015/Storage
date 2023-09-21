# -*- coding: utf-8 -*-
"""
Created on Wed Aug 23 16:21:52 2017

@author: HanKin
"""

import numpy as np

dic = dict()
dic['hejian'] = 23
dic['xieyue'] = 20
dic['sbd'] = 2
dic['wangning'] = 333

tmp1 = 'sbd'
tmp2 = 20
if tmp1 not in dic:
    print('no sbd')
else:
    print('sbd')

if tmp2 not in dic:
    print('no 20')
else:
    print('20')  
    
lis = []
lis.append(('a','b','c'))
print(lis)
print(type(lis))
#print(lis.shape)
print(len(lis))
lis = np.array(lis)
print(lis)
print(type(lis))
print(lis.shape)
lis = lis.reshape(3,-1)
print(lis)
print(type(lis))
print(lis.shape)
# 多维数组和矩阵表示和显示出来差不多
lis = np.mat(lis)
print(lis)
print(type(lis))
print(lis.shape)

# 还有这种操作
arr = np.array([1,2,3,4,2,6])
print(arr[2])
print(len(arr[:] == 2))
print(len(arr[arr[:] == 2]))
print(arr)

# 三元符号
ans = 1 if tmp1 in dic else 0
print(ans)









