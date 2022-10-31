# -*- coding: utf-8 -*-
"""
文 件 名: gc_example.py
文件描述: gc模块学习
作    者: HanKin
创建日期: 2022.10.31
修改日期：2022.10.31

Copyright (c) 2022 HanKin. All rights reserved.
"""

import subprocess, psutil, gc

mem1 = psutil.virtual_memory()
print(f"某程序前内存已使用：{mem1.used}")
print(f"某程序前内存剩余：{mem1.free}")
print(f"某程序前内存百分比：{mem1.percent}")

#app1 = subprocess.Popen(r'C:\Program Files\Git\git-bash.exe')
app1 = subprocess.Popen(r"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe")
app2 = subprocess.Popen(r"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe")
app3 = subprocess.Popen(r"C:\Program Files (x86)\Google\Chrome\Application\chrome.exe")

mem2 = psutil.virtual_memory()
print(f"某程序后内存已使用：{mem2.used}")
print(f"某程序后内存剩余：{mem2.free}")
print(f"某程序后内存百分比：{mem2.percent}")

app1.kill()
app2.kill()
app3.kill()

gc.collect()
mem3 = psutil.virtual_memory()
print(f"GC回收后内存已使用：{mem3.used}")
print(f"GC回收后内存剩余：{mem3.free}")
print(f"GC回收后内存百分比：{mem3.percent}")
