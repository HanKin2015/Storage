# -*- coding: utf-8 -*-
"""
文 件 名: parse_ini.py
文件描述: 解析ini文件（发现inf文件也是这种格式）
备    注: 
作    者: HanKin
创建日期: 2022.01.18
修改日期：2024.01.31

Copyright (c) 2024 HanKin. All rights reserved.
"""
# 导包
import configparser
import chardet

# 类实例化
config_parser = configparser.ConfigParser(allow_no_value=True, strict=False) # 允许重复值

# 定义文件路径
path = r'D:\Github\Storage\python\config\ini\conf.ini'

def detect_encoding(file_path):
    with open(file_path, 'rb') as f:
        rawdata = f.read()
    result = chardet.detect(rawdata)
    print(result['encoding'])
    return result['encoding']

# 注意文件编码格式
encoding = detect_encoding(path)
config_parser.read(path, encoding=encoding)

# 第一种读取ini文件方式
value = config_parser['select']['url']
print('第一种方法读取到的值：', value)

# 第二种读取ini文件方式，通过get方法
value = config_parser.get('select', 'url')
print('第二种方法读取到的值：', value)

# 第三种读取ini文件方式，读取到一个section中的所有数据，返回一个列表
value = config_parser.items('select')
print('第三种方法读取到的值：', value)

# 得到指定数据类型的数据
value = config_parser.getint('connect_mysql', 'port')
print('这是第三种方法读取到的值：', value)
print('这是第三种方法读取到的值的数据类型：', type(value))

# 将数据写入到ini文件中(可能需要删除login块)
config_parser.add_section('login') # 首先添加一个新的section
config_parser.set('login', 'username', 'admin')  # 写入数据
config_parser.set('login', 'password', '123456') # 写入数据
config_parser.write(open(path, 'w'))           # 保存数据

# 读取ini文件中所有的section
section = config_parser.sections()
print(section)

# 判断键是否存在，直接访问不存在的键会抛出异常
if config_parser.has_section("select"):
    value = config_parser.items('select')
    if config_parser.has_option("select", "name"):
        value = config_parser.get('select','url')

