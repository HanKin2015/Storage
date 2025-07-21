# -*- coding: utf-8 -*-
"""
文 件 名: 图像算术运算.py
文件描述: 图像算术运算
备    注: 
作    者: HanKin
创建日期: 2025.07.21
修改日期：2025.07.21

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2

# 读取两幅图像
img1 = cv2.imread('法斗.png')
img2 = cv2.imread('仓鼠.png')

# 1、图像加法
result = cv2.add(img1, img2)

# 2、图像减法
result = cv2.subtract(img1, img2)

# 3、图像除法
result = cv2.divide(img1, img2)

# 4、位与运算
result = cv2.bitwise_and(img1, img2)

# 5、位或运算
result = cv2.bitwise_or(img1, img2)

# 6、位非运算
result = cv2.bitwise_not(img1)

# 7、位异或运算
result = cv2.bitwise_xor(img1, img2)

# 8、图像混合
alpha = 0.7  # 第一幅图像的权重
beta = 0.3   # 第二幅图像的权重
gamma = 0    # 可选的标量值
result = cv2.addWeighted(img1, alpha, img2, beta, gamma)

# 显示结果
cv2.imshow('Result', result)
cv2.waitKey(0)
cv2.destroyAllWindows()