# -*- coding: utf-8 -*-
"""
文 件 名: Ui_MathTool.py
文件描述: 数学工具
作    者: HanKin
创建日期: 2023.05.19
修改日期：2023.05.19

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import unittest
from log import *

def dec_number_valid(number_str):
    """十进制数的合法性
    """
    
    if number_str.isdigit():
        return True
    return False

def hex_number_valid(number_str):
    """十六进制数的合法性
    """
    
    # all(c in string.hexdigits for c in s)
    try:
        int(number_str, 16)
        return True
    except ValueError:
        return False

def oct_number_valid(number_str):
    """八进制数的合法性
    """
    
    try:
        int(number_str, 8)
        return True
    except ValueError:
        return False

def bin_number_valid(number_str):
    """二进制数的合法性
    """
    
    try:
        int(number_str, 2)
        return True
    except ValueError:
        return False

def decimal_conversion(number_str, decimal_type):
    """进制转换
    """

    dec_number = None
    if decimal_type == '十进制':
        if dec_number_valid(number_str):
            dec_number = int(number_str, 10)
    elif decimal_type == '十六进制':
        if hex_number_valid(number_str):
            dec_number = int(number_str, 16)
    elif decimal_type == '八进制':
        if oct_number_valid(number_str):
            dec_number = int(number_str, 8)
    elif decimal_type == '二进制':
        if bin_number_valid(number_str):
            dec_number = int(number_str, 2)
    else:
        logger.error('not expected decimal type, {}'.format(decimal_type))

    if dec_number == None:
        logger.error('number string is invalid, {}'.format(number_str))
        return None, None, None, None
    hex_number = hex(dec_number)
    oct_number = oct(dec_number)
    bin_number = bin(dec_number)
    logger.info('{} {} {} {}'.format(bin_number, oct_number, dec_number, hex_number))
    logger.info('{} {} {} {}'.format(type(bin_number), type(oct_number), type(dec_number), type(hex_number)))
    return bin_number, oct_number, dec_number, hex_number

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

        self.assertEqual(decimal_conversion('010101', '二进制'), ('0b10101', '0o25', 21, '0x15'))
        self.assertEqual(decimal_conversion('D89', '十六进制'), ('0b110110001001', '0o6611', 3465, '0xd89'))
        self.assertEqual(decimal_conversion('D89', 16), (None, None, None, None))

def main():
    """主函数
    """

    unittest.main()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))