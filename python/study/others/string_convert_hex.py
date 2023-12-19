# -*- coding: utf-8 -*-
"""
文 件 名: string_convert_hex.py
文件描述: 字符串和十六进制之间转换
作    者: HanKin
创建日期: 2023.12.13
修改日期：2023.12.13

Copyright (c) 2023 HanKin. All rights reserved.
"""
shellcode = "\\x31\\xc9\\xf7\\xe1\\x51\\x68\\x2f\\x2f\\x73"
shellcode += "\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\xb0"
shellcode += "\\x0b\\xcd\\x80"
print(shellcode)
converted_shellcode = ""
bytes_list = shellcode.split("\\x")[1:]
print(len(bytes_list))
for byte in bytes_list:
    #print(byte)
    converted_shellcode += chr(int(byte, 16))
print(converted_shellcode)

string = "whoami"
hex_string = ""
for char in string:
    hex_string += "\\x%02x" % ord(char)
print(hex_string)