# -*- coding: utf-8 -*-
"""
文 件 名: 图像基本操作.py
文件描述: 图像基本操作
备    注: 
作    者: HanKin
创建日期: 2025.07.21
修改日期：2025.07.21

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2
import numpy as np

image = cv2.imread('仓鼠.png')   # 返回一个 NumPy 数组，异常则返回 None

## 1、访问和修改像素值
# 获取像素值 (BGR 格式)
pixel_value = image[100, 100]  # 获取 (100, 100) 处的像素值

# 修改像素值
image[10, 10] = [255, 255, 255]  # 将 (100, 100) 处的像素设置为白色

## 2、图像 ROI（Region of Interest）
# 获取 ROI
roi = image[50:150, 50:150]  # 获取 (50,50) 到 (150,150) 的区域

# 修改 ROI
image[50:150, 50:150] = [0, 255, 0]  # 将 ROI 区域设置为绿色

## 3、图像通道分离与合并
# 分离通道
b, g, r = cv2.split(image)

# 合并通道
merged_image = cv2.merge([b, g, r])

## 4、图像缩放、旋转、平移、翻转
# 缩放
print("image shape is {}".format(image.shape))
new_width = 100
new_height = 100
resized_image = cv2.resize(image, (new_width, new_height))

# 旋转
(width, height) = image.shape[:2]
center = (width // 2, height // 2)
rotation_matrix = cv2.getRotationMatrix2D(center, 45, 1.0)  # 旋转 45 度
rotated_image = cv2.warpAffine(image, rotation_matrix, (width, height))

# 平移
translation_matrix = np.float32([[1, 0, 100], [0, 1, 50]])  # 向右平移 100 像素，向下平移 50 像素
translated_image = cv2.warpAffine(image, translation_matrix, (width, height))

# 翻转
flip_code = 0
flipped_image = cv2.flip(image, flip_code)  # flip_code: 0 (垂直翻转), 1 (水平翻转), -1 (双向翻转)

# 显示图像
cv2.imshow("Display Window", flipped_image)

# 等待按键输入
cv2.waitKey(0)

# 关闭所有窗口
cv2.destroyAllWindows()