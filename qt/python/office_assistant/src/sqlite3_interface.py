# -*- coding: utf-8 -*-
"""
文 件 名: sqlite3_interface.py
文件描述: sqlite3数据库操作接口
作    者: HanKin
创建日期: 2024.02.27
修改日期：2024.02.27

Copyright (c) 2024 HanKin. All rights reserved.
"""

import time
import unittest
from log import *
import sqlite3

def open_sqlite3(db_path):
    """打开数据库，创建数据库连接
    """
    connection = sqlite3.connect(db_path)
    return connection

def close_sqlite3(connection):
    """关闭数据库，提交事务并关闭连接
    """
    connection.commit()
    connection.close()

def get_table_list(connection):
    """获取数据表列表
    sqlite_sequence 是 SQLite 数据库中的一个系统表，用于跟踪自增列的当前值。这个表是由 SQLite 自动创建和维护的，用于跟踪每个表中包含自增列的当前值。它是 SQLite 数据库的内部系统表之一。
    """
    # 创建游标对象
    cursor = connection.cursor()
    # 执行SQL语句查询表列表
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name!='sqlite_sequence'")
    data = cursor.fetchall()
    table_list = []
    for row in data:
        print(row[0])
        table_list.append(row[0])
    return table_list

def main():
    """主函数
    """

    db_name = r'D:\Github\Storage\sqlite3\runoob\testDB.db'
    connection = open_sqlite3(db_name)
    show_tables(connection)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))