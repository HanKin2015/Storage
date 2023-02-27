# -*- coding: utf-8 -*-
"""
文 件 名: convert_png_to_ico.py
文件描述: 把png转换为ico图标
作    者: HanKin
创建日期: 2023.02.27
修改日期：2023.02.27

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
from PIL import Image

def convert_png_to_ico():
    """把png转换为ico图标
    """
    
    # 获取目录下文件名
    files = os.listdir()
    # 图标大小
    size = (256, 256)

    # 给图标文件单独创建一个icon目录
    if not os.path.exists('icon'):
        os.mkdir('icon')

    for inName in files:
        # 分离文件名与扩展名
        tmp = os.path.splitext(inName)
        # 因为python文件跟图片在同目录，所以需要判断一下
        if tmp[1] == '.png':
            outName = tmp[0] + '.ico'
            # 打开图片并设置大小
            im = Image.open(inName).resize(size)
            try:
                # 图标文件保存至icon目录
                path = os.path.join('icon', outName)
                im.save(path)

                print('{} --> {}'.format(inName, outName))
            except IOError:
                print('connot convert :',inName)

def main():
    """主函数
    """
    
    png_img = Image.open(r'D:\Github\Storage\python\wmi\udev_detect\img\msg.png')
    print(png_img.size)
    ico_img = png_img.save(r'D:\Github\Storage\python\wmi\udev_detect\img\msg.ico')

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))