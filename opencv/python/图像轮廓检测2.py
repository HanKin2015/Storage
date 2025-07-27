# -*- coding: utf-8 -*-
"""
文 件 名: 图像轮廓检测2.py
文件描述: 图像轮廓检测
备    注: 
作    者: HanKin
创建日期: 2025.07.24
修改日期：2025.07.24

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2

# 读取图像
image = cv2.imread("仓鼠.png")

# 转换为灰度图
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# 二值化处理
ret, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

# 查找轮廓
contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# 绘制轮廓
cv2.drawContours(image, contours, -1, (0, 255, 0), 2)

# 显示结果
cv2.imshow("Contours", image)
cv2.waitKey(0)
cv2.destroyAllWindows()