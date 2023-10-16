# -*- coding: utf-8 -*-
"""
文 件 名: format_print.py
文件描述: 格式化输出
作    者: HanKin
创建日期: 2022.11.17
修改日期：2022.11.17

Copyright (c) 2022 HanKin. All rights reserved.
"""

print('%d小时%d分%d秒' % (10.1, 20.2, 30.3))    # 10小时20分30秒

# 将十进制数字字符串转换为十六进制
decimal_str = '255'
hex_str = hex(int(decimal_str))
print(hex_str)  # 0xff

# 使用Python的字符串格式化功能来输出四位的十六进制数，不足四位时补0
hex_num = 255
hex_str = '{:04x}'.format(hex_num)
print(hex_str)  # 00ff