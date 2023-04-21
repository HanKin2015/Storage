import ctypes
import win32con
import win32gui
from ctypes import wintypes

# 定义回调函数
def window_hook(nCode, wParam, lParam):
    print(111)
    if nCode == win32con.HC_ACTION:
        # 获取窗口句柄
        hwnd = ctypes.cast(lParam, ctypes.POINTER(ctypes.c_void_p)).contents.value
        # 获取窗口位置信息
        rect = win32gui.GetWindowRect(hwnd)
        x, y, w, h = rect
        print(f"Window {hwnd} moved to ({x}, {y}) with size ({w}, {h})")
    # 调用下一个钩子
    return ctypes.windll.user32.CallNextHookEx(hook_id, nCode, wParam, lParam)

window_callback = ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_void_p))(window_hook)

def keybord_msg_loop():
    """线程函数
    """

    # 安装钩子
    hHook = ctypes.windll.user32.SetWindowsHookExW(
        win32con.WH_KEYBOARD_LL,    # WH_KEYBOARD_LL\WH_CALLWNDPROC
        window_callback,
        None,
        0#ctypes.windll.kernel32.GetCurrentThreadId()
    )
    msg = ctypes.wintypes.MSG()
    while True:
        bRet = ctypes.windll.user32.GetMessageW(ctypes.byref(msg), None, 0, 0)
        if not bRet:
            print('bRet = {}, break exit'.format(bRet))
            break
        if bRet == -1:
            print('bRet = {}, WinError'.format(bRet))
            raise WinError(get_last_error())
        ctypes.windll.user32.TranslateMessage(ctypes.byref(msg))
        ctypes.windll.user32.DispatchMessageW(ctypes.byref(msg))
    
    # 卸载钩子
    ctypes.windll.user32.UnhookWindowsHookEx(hHook)

if __name__ == '__main__':
    import time
    import threading
    t = threading.Thread(target=keybord_msg_loop)
    t.start()
    while True:
        try:
            time.sleep(1)
        except KeyboardInterrupt:
            ctypes.windll.user32.PostThreadMessageW(t.ident, win32con.WM_QUIT, 0, 0)
            break
