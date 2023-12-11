# -*- coding: utf-8 -*-
"""
文 件 名: example_unittest_string.py
文件描述: 单元测试三种字符串方法，在调用测试脚本时添加 -v 参数使 unittest.main() 显示更为详细的信息
          python -v example_unittest_string.py
作    者: HanKin
创建日期: 2022.03.13
修改日期：2022.03.13

Copyright (c) 2022 HanKin. All rights reserved.
"""

import unittest

class TestStringMethods(unittest.TestCase):

    def test_upper(self):
        '''测试系统转换大写函数upper()
        '''
        self.assertEqual('foo'.upper(), 'FOO')

    def test_isupper(self):
        '''测试系统是否为大写字符串函数isupper()
        '''
        self.assertTrue('FOO'.isupper())
        self.assertFalse('Foo'.isupper())

    def test_split(self):
        '''测试系统切割函数split()
        '''
        s = 'hello world'
        self.assertEqual(s.split(), ['hello', 'world'])
        # check that s.split fails when the separator is not a string
        with self.assertRaises(TypeError):
            s.split(2)

if __name__ == '__main__':
    unittest.main()