import win32gui, win32ui
from win32api import GetSystemMetrics

def test1():
    dc = win32gui.GetDC(0)
    dcObj = win32ui.CreateDCFromHandle(dc)
    hwnd = win32gui.WindowFromPoint((0,0))
    monitor = (0, 0, GetSystemMetrics(0), GetSystemMetrics(1))

    while True:
        m = win32gui.GetCursorPos()
        dcObj.Rectangle((m[0], m[1], m[0]+30, m[1]+30))
        win32gui.InvalidateRect(hwnd, monitor, True) # Refresh the entire monitor

def test2():
    dc = win32gui.GetDC(0)
    dcObj = win32ui.CreateDCFromHandle(dc)
    dcObj.Rectangle((928, 508, 960, 540))

m=win32gui.GetCursorPos()
dc = win32gui.GetDC(0)
while True:
    n=win32gui.GetCursorPos()
    for i in range(n[0]-m[0]):
        win32gui.SetPixel(dc, m[0]+i, m[1], 0)
        win32gui.SetPixel(dc, m[0]+i, n[1], 0)
    for i in range(n[1]-m[1]):
        win32gui.SetPixel(dc, m[0], m[1]+i, 0)
        win32gui.SetPixel(dc, n[0], m[1]+i, 0)