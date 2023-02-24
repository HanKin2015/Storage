# -*- coding: utf-8 -*-
"""
文 件 名: remove_eference_dimension.py
文件描述: 移除引用标注
作    者: HanKin
创建日期: 2023.01.04
修改日期：2023.01.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
#import pynput
#import pyautogui
#import keybord
import PyQt5
#import PySide6.QtWidgets
import PySide6.QtCore


def main():
    """主函数
    """
    
    print(PySide6.__version__)
    print(PySide6.QtCore.__version__)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))