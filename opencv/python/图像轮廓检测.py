# -*- coding: utf-8 -*-
"""
文 件 名: 图像轮廓检测.py
文件描述: 图像轮廓检测
备    注: 
作    者: HanKin
创建日期: 2025.07.24
修改日期：2025.07.24

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2
import numpy as np

# 读取图像并转换为灰度图
image = cv2.imread('仓鼠.png', cv2.IMREAD_GRAYSCALE)

# 二值化处理
_, binary = cv2.threshold(image, 127, 255, cv2.THRESH_BINARY)
# 查找轮廓
contours, hierarchy = cv2.findContours(binary, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# 计算轮廓的面积
for contour in contours:
    area = cv2.contourArea(contour)
    print(f"Contour area: {area}")
    perimeter = cv2.arcLength(contour, True)
    print(f"Contour perimeter: {perimeter}")
    x, y, w, h = cv2.boundingRect(contour)
    cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
cv2.imshow('Bounding Rectangles', image)
cv2.waitKey(0)

# 创建一个空白图像
output = np.zeros_like(image)
# 绘制所有轮廓
cv2.drawContours(output, contours, -1, (255, 0, 0), 2)
cv2.imshow('Contours', output)
cv2.waitKey(0)

# 计算轮廓的最小外接矩形（旋转矩形）
for contour in contours:
    rect = cv2.minAreaRect(contour)
    box = cv2.boxPoints(rect)
    box = np.int0(box)
    cv2.drawContours(image, [box], 0, (0, 0, 255), 2)
cv2.imshow('Min Area Rectangles', image)
cv2.waitKey(0)

for contour in contours:
    (x, y), radius = cv2.minEnclosingCircle(contour)
    center = (int(x), int(y))
    radius = int(radius)
    cv2.circle(image, center, radius, (255, 0, 0), 2)
cv2.imshow('Min Enclosing Circles', image)
cv2.waitKey(0)

for contour in contours:
    epsilon = 0.01 * cv2.arcLength(contour, True)
    approx = cv2.approxPolyDP(contour, epsilon, True)
    cv2.drawContours(image, [approx], 0, (0, 255, 0), 2)
cv2.imshow('Approx Polygons', image)
cv2.waitKey(0)