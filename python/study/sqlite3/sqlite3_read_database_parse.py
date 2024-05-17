"""
文 件 名: sqlite3_read_database_parse.py
文件描述: 读取sqlite3数据库并解析其内容
备    注: 
作    者: HanKin
创建日期: 2024.05.10
修改日期：2024.05.10

Copyright (c) 2024 HanKin. All rights reserved.
"""
import sqlite3
import re

def parse_get_vpid(descriptor):
    """解析获取vpid
    """
    
    # 原始字符串
    raw_string = descriptor
    #print(type(raw_string))
    
    # 正则表达式模式
    # usbtreeview、box、usbview
    patterns = [r"idVendor\s+:\s+0x([0-9a-fA-F]+)\s+\(.*\)\nidProduct\s+:\s+0x([0-9a-fA-F]+)",
               r"idVendor\s+:\s+0x([0-9a-fA-F]+)\nidProduct\s+:\s+0x([0-9a-fA-F]+)",
               r"idVendor\s+0x([0-9a-fA-F]+)\s+.*\n\s+idProduct\s+0x([0-9a-fA-F]+)",
               r"idVendor:\s+0x([0-9a-fA-F]+)\s+.*\nidProduct:\s+0x([0-9a-fA-F]+)",
               r"idVendor:\s+0x([0-9a-fA-F]+)\nidProduct:\s+0x([0-9a-fA-F]+)"]

    # 使用正则表达式进行匹配
    for pattern in patterns:
        matches = re.search(pattern, raw_string)
        if matches:
            vendor_id = matches.group(1)
            product_id = matches.group(2)
            result = f"{vendor_id}:{product_id}"
            result = result.lower()
            print(result)
            return result
    print("未找到匹配的值")
    return None

raw_db = r"D:/Github/Storage/python/study/sqlite3/udev_info.db"
new_db = r"D:/Github/Storage/python/study/sqlite3/udev_info_.db"

connection = sqlite3.connect(raw_db)
cursor = connection.cursor()

# 获取数据表列表
cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name!='sqlite_sequence'")
data = cursor.fetchall()
table_list = []
for row in data:
    #print(row[0])
    table_list.append(row[0])

# 获取表里内容
cursor.execute("SELECT * FROM {}".format(table_list[0]))
data = cursor.fetchall()
for row in data:
    #print(row[2])
    parse_get_vpid(row[2])
connection.close()