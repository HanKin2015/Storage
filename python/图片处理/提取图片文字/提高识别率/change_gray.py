# -*- coding: utf-8 -*-
"""
文 件 名: change_gray.py
文件描述: 修改图片的灰度
作    者: HanKin
创建日期: 2022.07.26
修改日期：2022.07.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PIL import Image
from PIL import ImageEnhance
import pytesseract

img      = Image.open('test.png')
img      = img.convert('RGB')  #这里也可以尝试使用L
enhancer = ImageEnhance.Color(img)
enhancer = enhancer.enhance(0)
enhancer = ImageEnhance.Brightness(enhancer)
enhancer = enhancer.enhance(2)
enhancer = ImageEnhance.Contrast(enhancer)
enhancer = enhancer.enhance(8)
enhancer = ImageEnhance.Sharpness(enhancer)
img      = enhancer.enhance(20)
text     = pytesseract.image_to_string(img, lang='chi_sim')
print(text)