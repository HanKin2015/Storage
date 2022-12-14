# -*- coding: utf-8 -*-
"""
文 件 名: modify_screen_resolution.py
文件描述: 自动修改显示分辨率
作    者: HanKin
创建日期: 2022.12.12
修改日期：2022.12.12

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
import time
import os
from win32api import EnumDisplaySettings
from win32api import ChangeDisplaySettings

def modify_screen_resolution(width, height): 
    """修改屏幕分辨率
    """
    
    print('resolution: {} x {}'.format(width, height))
    dm = EnumDisplaySettings(None, 0)
    dm.PelsHeight = int(height)
    dm.PelsWidth = int(width)
    dm.BitsPerPel = 32
    dm.DisplayFixedOutput = 0
    ret = ChangeDisplaySettings(dm, 0)  # 成功返回0，目前我这边失败返回-2
    print('change display settings result: {}'.format(ret))

def auto_modify_screen_resolution():
    """自动修改屏幕分辨率
    """
    
    # 获取分辨率list
    with open('resolutions.txt', 'r') as f:
        all_resolutions = f.read()
    resolutions_list = all_resolutions.split('\n')

    while True:
        for resolutions in resolutions_list:
            if "*" in resolutions:
                # 获取宽度和高度
                height = resolutions.split('*')[-1]
                width = resolutions.split('*')[0]
                print('resolution: {} x {}'.format(width, height))
                
                # 切换
                dm = EnumDisplaySettings(None, 0)
                dm.PelsHeight = int(height)
                dm.PelsWidth = int(width)
                dm.BitsPerPel = 32
                dm.DisplayFixedOutput = 0
                ret = ChangeDisplaySettings(dm, 0)
                print('change display settings result: {}'.format(ret))
                
                # sleep 2s一下
                time.sleep(2)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    params = sys.argv
    print('{} len(params) = {}'.format(params[0], len(params)))
    if len(params) < 2:
        auto_modify_screen_resolution()
    else:
        modify_screen_resolution(params[1], params[2])

    end_time = time.time()
    print('process spend {} s.'.format(round(end_time - start_time, 3)))