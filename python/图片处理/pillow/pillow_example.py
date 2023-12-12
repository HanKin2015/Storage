# -*- coding: utf-8 -*-
"""
文 件 名: pillow_example.py
文件描述: Pillow 是一个强大且易用的 Python 图像处理库，它提供了丰富的图像操作功能，可以满足绝大部分的图像处理需求
作    者: HanKin
创建日期: 2023.12.12
修改日期：2023.12.12

Copyright (c) 2023 HanKin. All rights reserved.
"""
from PIL import Image, ImageFilter, ImageEnhance

# 打开图像文件
img = Image.open('example.png')

# 显示图像
img.show()

# 转为灰度图像
img_gray = img.convert('L')
img_gray.show()

# 应用模糊滤镜
img_blur = img.filter(ImageFilter.BLUR)
img_blur.show()

# 旋转 45 度
img_rotate = img.rotate(45)
img_rotate.show()

# 调整对比度
enhancer = ImageEnhance.Contrast(img)
img_enhanced = enhancer.enhance(2.0)  # 提高对比度
img_enhanced.show()

# 裁剪
box = (50, 50, 200, 200)  # (左, 上, 右, 下)
img_crop = img.crop(box)
img_crop.show()

# 保存图像
img.save('example_processed.jpg')