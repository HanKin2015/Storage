# -*- coding: utf-8 -*-
"""
文 件 名: keyboard_hook_example.py
文件描述: 给键盘增加一个钩子
作    者: HanKin
创建日期: 2023.04.19
修改日期：2023.04.19

Copyright (c) 2023 HanKin. All rights reserved.
"""

import ctypes
from ctypes import wintypes

user32 = ctypes.windll.user32

HC_ACTION      = 0
WH_KEYBOARD_LL = 13
WH_MOUSE_LL    = 14

WM_QUIT        = 0x0012
WM_MOUSEMOVE   = 0x0200
WM_LBUTTONDOWN = 0x0201
WM_LBUTTONUP   = 0x0202
WM_RBUTTONDOWN = 0x0204
WM_RBUTTONUP   = 0x0205
WM_MBUTTONDOWN = 0x0207
WM_MBUTTONUP   = 0x0208
WM_MOUSEWHEEL  = 0x020A
WM_MOUSEHWHEEL = 0x020E

# 定义钩子函数
def keyboard_hook_callback(nCode, wParam, lParam):
    if nCode >= HC_ACTION:
        # 获取键盘事件信息
        key_event = ctypes.cast(lParam, ctypes.POINTER(ctypes.c_char)).contents
        print(type(key_event))
        print(key_event, key_event.value)
        key_str = key_event.value.decode('utf-8')
        print(key_str)
    # 调用下一个钩子
    return user32.CallNextHookEx(None, nCode, wParam, lParam)

# 将callback_func函数转换为函数指针类型
HOOKPROC = ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_void_p))(keyboard_hook_callback)

def keybord_msg_loop():
    # 安装钩子
    hHook = user32.SetWindowsHookExW(
        WH_KEYBOARD_LL,
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
            user32.PostThreadMessageW(t.ident, WM_QUIT, 0, 0)
            break
