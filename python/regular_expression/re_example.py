# -*- coding: utf-8 -*-
"""
文 件 名: re_example.py
文件描述: 学习正则表达式
作    者: HanKin
创建日期: 2023.09.19
修改日期：2023.09.19

Copyright (c) 2023 HanKin. All rights reserved.
"""

import re
import time

def test():
    version = """ABC5.5.1
banana M4.30_20101213
logs 4.1_20080301
apple 4.1_20090227
fox 4.30_20090227
dhcp 4.1_20080615
cluster 1.4_20100105
update date 2013-04-09
abc ABC5.5.1.210 Build20220310
build-abc-210 2022-03-10
update-abc 2022-03-10
XIAOMI_10PRO1.2.0
abc-sp 202305231150-ip-COMMON-04
"""
    version_list = version.split("\n")[:-1]
    version_list = [i.replace("\t", "  ") for i in version_list]
    pattern = r"ABC\d\.\d\.\d+\.\d+"
    version_row = [elem for elem in version_list if re.search(pattern, elem)]
    print(version_row)
    version = re.search("\d\.\d\.\d+.\d+", version_row[0]).group()
    print(version)

def main():
    test()

if __name__ == '__main__':
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))
 