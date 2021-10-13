# -*- coding: utf-8 -*-
"""
@description:
    学习python容器

@author: hankin
@date  : 2021.06.01
	
Copyright (c) 2021 HanKin. All rights reserved.
"""

import numpy as np

# 1、操作数组
arr = np.arange(0, 10).reshape(2, 5)
print("数组元素数量:", arr.size, "数组形状:", arr.shape, len(arr), len(arr[0]))

## 默认优先行遍历
for elem in arr:
    print(elem)
    
print(arr)