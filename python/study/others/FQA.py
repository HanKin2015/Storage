# -*- coding: utf-8 -*-
"""
文 件 名: FQA.py
文件描述: 一些问答问题解决方案
备    注: 
作    者: HanKin
创建日期: 2023.11.27
修改日期：2023.11.27

Copyright (c) 2023 HanKin. All rights reserved.
"""
# 1、由['a', 'b', 'c']变为['c', 'a', 'b', 'c']，有没有优雅一点的写法
lst = ['a', 'b', 'c']
lst.insert(0, lst[-1])
print(lst)  # ['c', 'a', 'b', 'c']
lst = ['a', 'b', 'c']
lst.insert(0, lst.pop())
lst.append(lst[0])
print(lst)  # ['c', 'a', 'b', 'c']

# 2、从5亿行数据中，筛选出重复次数在1000行的数据行
num = 1000
J_PF = df.groupby(df.column.values.tolist()).filter(lambda x_group: x_group.shape[0] >= int(num))

s_x_list = [pd.read_csv(i, header=None)
    .fillna(0.0)
    .astype(int, errors="ignore")
    .drop_duplicates()
    .assign(所属文件夹=os.path.basename(os.path.dirname(i)))
    for i in file_all]
from itertools import accumulate
res_iter = accumulate(s_x_list, lambda x, y: x.merge(y, how='outer'))
for i in range(len(s_x_list)):
    s_x_pdf = next(res_iter)
print(s_x_pdf)

# 3、pandas如何将下图这个数据格式，改为%Y-%m-%d这种格式
import pandas as pd
date1 = '2023/03/20'
res = pd.to_datetime(date1).strftime('%Y-%m-%d')
print(res)

# 4、列表下标起始位置
lst = [1, 2, 3, 4]
print(lst[2])   # 3 列表起始序号为0
    
# 5、输出十六进制格式
num = 1234
print("0x{:04x}".format(num))   # 0x04d2
print("0x{:04X}".format(num))   # 0x04D2

# 6、匹配vendor
device_id = '05e4:0690'
if int(device_id[:4], 16) == 0x05e3:
    print("{} device's vendor is 0x05e3".format(device_id))
else:
    print("{} device's vendor is not 0x05e3".format(device_id))
    
# 7、匹配vid和pid
device_id = '05e4:0690'
BOX_BUILT_IN_DEVICES = [{0x09da, 0x0999}, {0x9d69, 0x0003}, {0x09da, 0x5999}, {0x9d69, 0x0002}, {0x9d69, 0x0009},
                        {0x0929, 0x2599}, {0x05e3, 0x0690}, {0x0938, 0x7900}, {0x09da, 0x8952}, {0x9a90, 0x0209},
                        {0x09da, 0x895b}, {0x9987, 0x07e6}, {0x9a90, 0x0909}, {0x9a90, 0x0909}]
vid = int(device_id[:4], 16)
pid = int(device_id[6:], 16)
vid_pid = {vid, pid}
print(type(vid_pid), vid_pid)
if vid_pid in BOX_BUILT_IN_DEVICES:
    print("{} in BOX_BUILT_IN_DEVICES".format(device_id))
else:
    print("{} in not BOX_BUILT_IN_DEVICES".format(device_id))