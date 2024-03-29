# -*- coding: utf-8 -*-
"""
文 件 名: windows_hook_example.py
文件描述: 给一个exe进程增加一个钩子
作    者: HanKin
创建日期: 2023.04.19
修改日期：2023.04.19

Copyright (c) 2023 HanKin. All rights reserved.
"""

import ctypes
from ctypes import wintypes
import win32con
import win32process
import win32gui

user32 = ctypes.windll.user32
target_pid = 16472  # 目标进程notepad.exe记事本的PID

# 定义钩子函数
def callback_func(nCode, wParam, lParam):
    print('2')
    if nCode == win32con.HC_ACTION:
        hwnd = lParam[0]
        pid = win32process.GetWindowThreadProcessId(hwnd)[1]
        if pid == target_pid:
            title = win32gui.GetWindowText(hwnd)
            clsname = win32gui.GetClassName(hwnd)
            rect = win32gui.GetWindowRect(hwnd)
            print(f"{title} ({clsname}): {rect}")
    return user32.CallNextHookEx(None, nCode, wParam, lParam)

# 将callback_func函数转换为函数指针类型
HOOKPROC = ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_void_p))(callback_func)

def keybord_msg_loop():
    """线程函数
    """

    # 安装钩子
    hHook = user32.SetWindowsHookExW(
        win32con.WH_CALLWNDPROC,    # WH_KEYBOARD_LL\WH_CALLWNDPROC
        HOOKPROC,
        None,
        0
    )
    msg = ctypes.wintypes.MSG()
    while True:
        bRet = user32.GetMessageW(ctypes.byref(msg), None, 0, 0)
        if not bRet:
            print('bRet = {}, break exit'.format(bRet))
            break
        if bRet == -1:
            print('bRet = {}, WinError'.format(bRet))
            raise WinError(get_last_error())
        user32.TranslateMessage(ctypes.byref(msg))
        user32.DispatchMessageW(ctypes.byref(msg))
    
    # 卸载钩子
    user32.UnhookWindowsHookEx(hHook)

if __name__ == '__main__':
    import time
    import threading
    t = threading.Thread(target=keybord_msg_loop)
    t.start()
    while True:
        try:
            time.sleep(1)
        except KeyboardInterrupt:
            user32.PostThreadMessageW(t.ident, win32con.WM_QUIT, 0, 0)
            break
