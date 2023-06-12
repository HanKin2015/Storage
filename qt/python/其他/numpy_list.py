lst = [[[1, 2, 3], [4, 5, 6]], [[7, 8, 9], [10, 11, 12]]]
print(lst)

import numpy as np
print(np.array(lst))

# 转换为数组
arr = []
for i in range(len(lst)):
    arr2d = []
    for j in range(len(lst[i])):
        arr1d = []
        for k in range(len(lst[i][j])):
            arr1d.append(lst[i][j][k])
        arr2d.append(arr1d)
    arr.append(arr2d)

# 打印数组
print(arr)