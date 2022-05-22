# -*- coding: utf-8 -*-
"""
文 件 名: unittest_time_stamp_to_time.py
文件描述: 单元测试
作    者: HanKin
创建日期: 2022.02.17
修改日期：2022.02.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

import unittest
import time_stamp_to_time

class TestCommonLibaryMethods(unittest.TestCase):
    def test_time_stamp_to_time(self):
        self.assertEqual(time_stamp_to_time.time_stamp_to_time(1479264792), ('2022-11-16 10:53:12'))

if __name__ == '__main__':
    unittest.main()
    
    
    