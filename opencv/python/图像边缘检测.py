# -*- coding: utf-8 -*-
"""
文 件 名: 图像边缘检测.py
文件描述: 图像边缘检测
备    注: 
作    者: HanKin
创建日期: 2025.07.24
修改日期：2025.07.24

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2
import numpy as np

# 读取图像
image = cv2.imread('仓鼠.png', cv2.IMREAD_GRAYSCALE)

# 应用 Canny 边缘检测
edges = cv2.Canny(image, 100, 200)

# 计算 x 方向的梯度
sobel_x = cv2.Sobel(image, cv2.CV_64F, 1, 0, ksize=3)
# 计算 y 方向的梯度
sobel_y = cv2.Sobel(image, cv2.CV_64F, 0, 1, ksize=3)
# 计算梯度幅值
sobel_combined = np.sqrt(sobel_x**2 + sobel_y**2)

# 应用 Laplacian 算子
laplacian = cv2.Laplacian(image, cv2.CV_64F)

# 显示结果
cv2.imshow('Canny Edges', laplacian)
cv2.waitKey(0)
cv2.destroyAllWindows()