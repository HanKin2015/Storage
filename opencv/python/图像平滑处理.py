# -*- coding: utf-8 -*-
"""
文 件 名: 图像平滑处理.py
文件描述: 图像平滑处理
备    注: 
作    者: HanKin
创建日期: 2025.07.24
修改日期：2025.07.24

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2

# 读取图像
image = cv2.imread('仓鼠.png')

# 应用均值滤波
blurred_image = cv2.blur(image, (5, 5))

# 应用高斯滤波
blurred_image = cv2.GaussianBlur(image, (5, 5), 0)

# 应用中值滤波
blurred_image = cv2.medianBlur(image, 5)

# 应用双边滤波
blurred_image = cv2.bilateralFilter(image, 9, 75, 75)

# 显示结果
cv2.imshow('Blurred Image', blurred_image)
cv2.waitKey(0)
cv2.destroyAllWindows()