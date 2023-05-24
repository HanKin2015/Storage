# -*- coding: utf-8 -*-
"""
文 件 名: math_interface.py
文件描述: 数学工具接口
作    者: HanKin
创建日期: 2023.05.19
修改日期：2023.05.24

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import unittest
from log import *
import math

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
    if decimal_type == 'DEC':
        if dec_number_valid(number_str):
            dec_number = int(number_str, 10)
    elif decimal_type == 'HEX':
        if hex_number_valid(number_str):
            dec_number = int(number_str, 16)
    elif decimal_type == 'OCT':
        if oct_number_valid(number_str):
            dec_number = int(number_str, 8)
    elif decimal_type == 'BIN':
        if bin_number_valid(number_str):
            dec_number = int(number_str, 2)
    else:
        logger.error('not expected decimal type, {}'.format(decimal_type))

    if dec_number == None:
        logger.error('number string is invalid, {} {}'.format(number_str, decimal_type))
        return None, None, None, None
    hex_str = hex(dec_number)
    oct_str = oct(dec_number)
    bin_str = bin(dec_number)
    logger.info('{} {} {} {}'.format(bin_str, oct_str, dec_number, hex_str))
    logger.info('{} {} {} {}'.format(type(bin_str), type(oct_str), type(dec_number), type(hex_str)))
    return bin_str, oct_str, dec_number, hex_str

def find_common_divisors2s(a, b):
    """我咋感觉这个更快呢O(sqrt(gcd(a,b)))
    """
    
    gcd_ab = gcd(a, b)
    divisors = set([1, gcd_ab])
    for i in range(2, int(gcd_ab**0.5)+1):
        if gcd_ab % i == 0:
            divisors.add(i)
            divisors.add(gcd_ab // i)
    return sorted(list(divisors))

def prime_factors(n):
    """求质因数
    """
    
    factors = []
    i = 2
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors.append(i)
    if n > 1:
        factors.append(n)
    return factors

def find_common_divisors(a, b):
    """将a和b分别分解成质因数的乘积，然后找到它们的公共质因数，最后将这些质因数乘起来即可得到a和b的所有公约数O(log(min(a,b)))
    """
    
    factors_a = prime_factors(a)
    factors_b = prime_factors(b)
    common_factors = set(factors_a) & set(factors_b)
    divisors = set([1])
    for factor in common_factors:
        for i in range(1, min(factors_a.count(factor), factors_b.count(factor))+1):
            divisors.add(factor**i)
    return sorted(list(divisors))

def get_gcd_lcm(a, b):
    """
    """
    
    if dec_number_valid(a) and dec_number_valid(b):
        a = int(a, 10)
        b = int(b, 10)
    else:
        return None, None, None
    gcd = math.gcd(a, b)
    #lcm = math.lcm(a, b)    # python3.9版本才新增
    lcm = a * b // gcd
    cd = find_common_divisors(a, b)
    return gcd, lcm, cd

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