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
    """
    # 创建游标对象
    cursor = connection.cursor()
    # 执行SQL语句查询表列表
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")
    data = cursor.fetchall()
    table_list = []
    for row in data:
        print(row[0])
        table_list.append(row[0])
    return table_list

class TestMathInterfaceMethods(unittest.TestCase):
    """math_interface文件的单元测试
    """
    
    def test_dec_number_valid(self):
        """测试十进制数的合法性
        """
        
        self.assertEqual(dec_number_valid('1234567'), True)
        self.assertTrue(dec_number_valid('5915'))
        self.assertFalse(dec_number_valid('59ABC'))

    def test_hex_number_valid(self):
        """测试十六进制数的合法性
        """
        
        self.assertTrue(hex_number_valid('59ABC'))
        self.assertFalse(hex_number_valid('9EFG'))

    def test_oct_number_valid(self):
        """测试八进制数的合法性
        """

        self.assertTrue(oct_number_valid('01234567'))
        self.assertFalse(oct_number_valid('87654'))

    def test_bin_number_valid(self):
        """测试二进制数的合法性
        """

        self.assertTrue(bin_number_valid('010101'))
        self.assertFalse(bin_number_valid('01201'))

    def test_decimal_conversion(self):
        """测试进制转换
        """

        self.assertEqual(decimal_conversion('010101', 'BIN'), ('0b10101', '0o25', 21, '0x15'))
        self.assertEqual(decimal_conversion('D89', 'HEX'), ('0b110110001001', '0o6611', 3465, '0xd89'))
        self.assertEqual(decimal_conversion('D89', 16), (None, None, None, None))

    def test_find_common_divisors(self):
        """测试所有公约数
        """
        
        self.assertEqual(find_common_divisors(12, 8), [1, 2, 4])

def main():
    """主函数
    """

    #unittest.main()
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