# -*- coding: utf-8 -*-
"""
文 件 名: special_system32_dir.py
文件描述: 特殊的system32文件夹，文件夹重定向
参    考: 
作    者: HanKin
创建日期: 2024.01.24
修改日期：2024.01.24

Copyright (c) 2024 HanKin. All rights reserved.
"""
import platform
import os

def solve1():
    system32_path = r"C:\Windows\System32"
    bit_number = platform.architecture()[0]
    print(bit_number)
    if bit_number == '32bit':
        system32_path = r"C:\Windows\Sysnative"
    
    if os.path.exists(os.path.join(system32_path, r"drivers\vdiusbfilter.sys")):
        print("vdiusbfilter.sys file exists")
    else:
        print("vdiusbfilter.sys file not exists")

import ctypes
class disable_file_system_redirection:
    _disable = ctypes.windll.kernel32.Wow64DisableWow64FsRedirection
    _revert = ctypes.windll.kernel32.Wow64RevertWow64FsRedirection
    def __enter__(self):
        print("enter")
        self.old_value = ctypes.c_long()
        self.success = self._disable(ctypes.byref(self.old_value))
    def __exit__(self, type, value, traceback):
        print("exit")
        if self.success:
            self._revert(self.old_value)

def solve2():
    disable_file_system_redirection().__enter__()
    
    if os.path.exists(r"C:\Windows\System32\drivers\vdiusbfilter.sys"):
        print("vdiusbfilter.sys file exists")
    else:
        print("vdiusbfilter.sys file not exists")
    
    #disable_file_system_redirection().__exit__(None, None, None)
    
if __name__ == '__main__':
    solve1()
    solve2()
    