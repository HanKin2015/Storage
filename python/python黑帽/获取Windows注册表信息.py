# -*- coding: utf-8 -*-
"""
文 件 名: 获取windows注册表信息.py
文件描述: 通过wmi库
作    者: HanKin
创建日期: 2023.03.31
修改日期：2023.03.31

Copyright (c) 2023 HanKin. All rights reserved.
"""

import winreg as wg

#创建键
subDir = r"Software\Microsoft\Windows\CurrentVersion\Explorer"
key_test = wg.OpenKey(wg.HKEY_CURRENT_USER, subDir)
wg.CreateKey(key_test, 'Eastmount')
wg.CloseKey(key_test)

#获取键值数据项值
subDir = r"Software\Microsoft\Windows\CurrentVersion\Explorer\Eastmount"
key_test = wg.OpenKey(wg.HKEY_CURRENT_USER, subDir)
value,type_ = wg.QueryValueEx(key_test,'yxz')
print(value)
print(type_)

#创建键值数据项
subDir = r"Software\Microsoft\Windows\CurrentVersion\Explorer\Eastmount"
key_test = wg.OpenKey(wg.HKEY_CURRENT_USER, subDir)
print(key_test)
#PermissionError: [WinError 5] 拒绝访问
wg.SetValueEx(key_test,'data','',wg.REG_SZ,'0') 
wg.CloseKey(key_test)

#删除键值数据项
subDir = r"Software\Microsoft\Windows\CurrentVersion\Explorer\Eastmount"
key_test = wg.OpenKey(wg.HKEY_CURRENT_USER,subDir,0,wg.KEY_WRITE)
wg.DeleteValue(key_test,'yxz')
wg.CloseKey(key_test)

