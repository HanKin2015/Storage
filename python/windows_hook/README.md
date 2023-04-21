参考：https://qa.1r1g.com/sf/ask/2196541861/

## 坑点1
```
# 安装钩子
hook_id = user32.SetWindowsHookExA(
    13,  # WH_KEYBOARD_LL
    ctypes.cast(ctypes.addressof(callback_func), ctypes.c_void_p),
    ctypes.windll.kernel32.GetModuleHandleW(None),
    0
)
```
两个错误点，首先ctypes.cast(ctypes.addressof(callback_func), ctypes.c_void_p)需要指针函数进行转换。
然后ctypes.windll.kernel32.GetModuleHandleW(None)直接写成None。

## 坑点2
```
window_callback = ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_void_p))

def keybord_msg_loop():
    """线程函数
    """

    # 安装钩子
    hHook = ctypes.windll.user32.SetWindowsHookExW(
        win32con.WH_KEYBOARD_LL,    # WH_KEYBOARD_LL\WH_CALLWNDPROC
        window_callback(window_hook),
        None,
        0#ctypes.windll.kernel32.GetCurrentThreadId()
    )
```
为啥上面的写法会导致程序崩溃，但是如果把参数写进指针函数就ok了。
```
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
```

