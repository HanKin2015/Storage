# -*- coding: utf-8 -*-
"""
文 件 名: 图像形态学操作.py
文件描述: 图像形态学操作
备    注: 
作    者: HanKin
创建日期: 2025.07.24
修改日期：2025.07.24

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2
import numpy as np

# 读取图像
image = cv2.imread('仓鼠.png', 0)

# 定义结构元素
kernel = np.ones((5,5), np.uint8)

# 腐蚀操作
eroded_image = cv2.erode(image, kernel, iterations=1)

# 膨胀操作
dilated_image = cv2.dilate(image, kernel, iterations=1)

# 开运算
opened_image = cv2.morphologyEx(image, cv2.MORPH_OPEN, kernel)

# 闭运算
closed_image = cv2.morphologyEx(image, cv2.MORPH_CLOSE, kernel)

# 形态学梯度
gradient_image = cv2.morphologyEx(image, cv2.MORPH_GRADIENT, kernel)

# 显示结果
cv2.imshow('Eroded Image', gradient_image)
cv2.waitKey(0)
cv2.destroyAllWindows()