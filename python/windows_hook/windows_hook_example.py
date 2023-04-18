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
def callback_func(nCode, wParam, lParam):
    print('2222')
    if nCode == HC_ACTION:
        print('keybord')
    # 处理钩子事件
    return user32.CallNextHookEx(None, nCode, wParam, lParam)

# 将callback_func函数转换为函数指针类型
HOOKPROC = ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_void_p))(callback_func)

def keybord_msg_loop():
    # 安装钩子
    hHook = user32.SetWindowsHookExW(
        WH_KEYBOARD_LL,
        HOOKPROC,
        ctypes.windll.kernel32.GetModuleHandleW(None),
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
