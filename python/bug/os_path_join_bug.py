# -*- coding: utf-8 -*-
"""
文 件 名: os_path_join_bug.py
文件描述: 使用os.path.join函数拼接地址路径存在问题
作    者: HanKin
创建日期: 2023.12.21
修改日期：2023.12.21

Copyright (c) 2023 HanKin. All rights reserved.
"""
import datetime
import os

# 使用exec函数会将反斜杠 \ 被误解释视为转义字符
file_path = "img\\screenshot\\2023-12-21.png"
exec("msg = 'this file path is {}'".format(file_path), globals())
print(msg)

# repr() 函数将对象转化为供解释器读取的形式。
file_path = "img\\screenshot\\2023-12-21.png"
exec("msg = 'this file path is {}'.format(repr(file_path))", globals())
print(msg)

now_time = datetime.datetime.now()
img_name = '{}-{}-{}_{}:{}:{}.png'.format(now_time.year, now_time.month, now_time.day,
                                           now_time.hour, now_time.minute, now_time.second)
file_path = os.path.join('img', 'screenshot', img_name)
print(file_path)

file_path = "{}".format(os.path.join('img', 'screenshot', img_name))
print(file_path)

# 失败
exec("file_path = '{}'".format(os.path.normpath(os.path.join('img', 'screenshot', img_name))))
print(file_path)

# 失败
exec("file_path = '{}'".format(file_path))
print(file_path)

# 失败
exec('file_path = "{}"'.format(file_path))
print(file_path)

# 失败
exec('file_path = "{}"'.format(os.path.join('img', 'screenshot', img_name)))
print(file_path)
exec('print(file_path)')