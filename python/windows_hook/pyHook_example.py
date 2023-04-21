# 如果你在使用Python 3.x版本，那么pyHook库可能不再支持。你可以尝试使用pynput库来替代pyHook，它也可以用于监听和控制键盘和鼠标事件。
# 注意：pyHook库只支持32位的Python解释器，如果你使用的是64位的Python解释器，你需要安装32位的Python解释器才能使用pyHook库。

import win32api
import win32con
import win32gui
import pythoncom
import pyHook

def on_keyboard_event(event):
    if event.Key == 'Escape':
        win32api.PostQuitMessage()
    return True

def main():
    # 创建钩子管理器
    hm = pyHook.HookManager()
    # 监听键盘事件
    hm.KeyDown = on_keyboard_event
    hm.HookKeyboard()

    # 进入消息循环
    pythoncom.PumpMessages()

if __name__ == '__main__':
    main()
