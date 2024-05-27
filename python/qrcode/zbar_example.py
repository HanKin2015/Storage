# -*- coding: utf-8 -*-
"""
文 件 名: zbar_example.py
文件描述: https://pypi.org/search/?q=zbar&o=
备    注：似乎不维护了，zbar不支持python3。https://blog.csdn.net/u013735688/article/details/122798047
          https://blog.csdn.net/qq_42109746/article/details/88233758
作    者: HanKin
创建日期: 2024.05.23
修改日期：2024.05.23

Copyright (c) 2024 HanKin. All rights reserved.
"""
import zbar
from PIL import Image
 
scanner = zbar.ImageScanner()
scanner.parse_config('enable')
 
pil = Image.open('chinese_qrcode.png').convert('L')
width, height = pil.size
raw = pil.tobytes()
 
image = zbar.Image(width, height, 'Y800', raw)
scanner.scan(image)
 
for symbol in image:
    print('decoded', symbol.type, 'symbol', symbol.data)
 
image.clear()
del image
scanner.cleanup()