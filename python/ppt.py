# enconding:utf-8
import time
import os
import sys
import shutil
from pykeyboard import PyKeyboard
from lib.office_util import EasyPpt
from lib.comm_util import windows_setfore,max_window

k = PyKeyboard()
try:
    ppt_path = r"C:/exe/ppt/test.ppt"
    temp_ppt_path = r"C:/exe/ppt/temp.ppt"
    shutil.copy(ppt_path, temp_ppt_path)
    ppt = EasyPpt(ppt_path)
    max_window()
    while True:
        windows_setfore("temp.pptx")
        # 通过Shift+F5放映PPT
        k.press_key(k.shift_key)
        k.tap_key(k.function_keys[5])
        k.release_key(k.shift_key)
        # 切换幻灯片
        for index in range(0,10):
            k.press_key(k.down_key)
            time.sleep(1)
        for index in range(0,10):
            k.press_key(k.up_key)
            time.sleep(1)
        k.tap_key(k.escape_key)
        time.sleep(2)
except Exception as e:
    sys.exit()









