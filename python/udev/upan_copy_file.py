# -*- coding: utf-8 -*-
"""
文 件 名: upan_copy_file.py
文件描述: U盘拷贝文件
作    者: HanKin
创建日期: 2021.09.01
修改日期：2021.09.01

Copyright (c) 2021 HanKin. All rights reserved.
"""

import os
from time import sleep
import datetime
import hashlib
import sys

u_dick = "D:\\"


def get_md5(path):
    """
    获取文件的md5值
    """
    if os.path.isfile(path):
        rb = open(path, 'rb')
        rb_md5 = hashlib.md5()
        rb_md5.update(rb.read())
        return rb_md5.hexdigest()
    else:
        print("{}:the file_path is not a file".format(path))
        return ""


i = 1
with open('upan_copy_file.log', 'a+') as f:
    f.write("{}-----{}---\n".format(i, datetime.datetime.now()))
file_md5 = get_md5("upan_copy_file_data.txt")
os.system("del upan_copy_file_data.txt")
while True:
    print(i)
    print(datetime.datetime.now())

    res = os.system("copy /Y upan_copy_file_data.txt {}".format(u_dick))
    if res != 0:
        with open('upan_copy_file.log', 'a+') as f:
            f.write("{}-----{}---:{}\n".format(i, datetime.datetime.now(), res))
    sleep(3)

    u_md5 = get_md5("{}upan_copy_file_data.txt".format(u_dick))
    if u_md5 != file_md5:
        f.write("{}-----{}---:{}\n".format(i, datetime.datetime.now(), "dev copy to u the md5 is change"))
        sys.exit()
    os.system("del upan_copy_file_data.txt")

