# -*- coding: utf-8 -*-
"""
文 件 名: 图像阈值处理.py
文件描述: 图像阈值处理
备    注: 
作    者: HanKin
创建日期: 2025.07.21
修改日期：2025.07.21

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2

# 读取图像
"""
0 或 cv2.IMREAD_GRAYSCALE：
将图像强制转换为灰度图像（单通道）读取，无论原始图像是否为彩色。此时返回的 img 是一个二维数组，每个像素值代表灰度强度（0-255）。

1 或 cv2.IMREAD_COLOR（默认值）：
将图像读取为彩色图像（三通道 BGR），忽略原始透明度通道（如存在）。

-1 或 cv2.IMREAD_UNCHANGED：
读取图像的原始格式，包括透明度通道（如 PNG 图像的 Alpha 通道）。
"""
img = cv2.imread('仓鼠.png', 0)

# 1、简单阈值处理
"""
cv2.THRESH_BINARY: 如果像素值大于阈值，则赋予 maxval，否则赋予 0。
cv2.THRESH_BINARY_INV: 与 cv2.THRESH_BINARY 相反，如果像素值大于阈值，则赋予 0，否则赋予 maxval。
cv2.THRESH_TRUNC: 如果像素值大于阈值，则赋予阈值，否则保持不变。
cv2.THRESH_TOZERO: 如果像素值大于阈值，则保持不变，否则赋予 0。
cv2.THRESH_TOZERO_INV: 与 cv2.THRESH_TOZERO 相反，如果像素值大于阈值，则赋予 0，否则保持不变。
"""
ret, thresh = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)

# 2、自适应阈值处理
"""
cv2.ADAPTIVE_THRESH_MEAN_C: 阈值是邻域的平均值减去常数 C。
cv2.ADAPTIVE_THRESH_GAUSSIAN_C: 阈值是邻域的加权平均值减去常数 C，权重由高斯函数确定。
thresholdType: 阈值处理的类型，通常为 cv2.THRESH_BINARY 或 cv2.THRESH_BINARY_INV。
"""
thresh = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 2)

# 3、Otsu's 二值化
"""
大津法（OTSU）是一种确定图像二值化分割阈值的算法，由日本学者大津于1979年提出。
从大津法的原理上来讲，该方法又称作最大类间方差法，因为按照大津法求得的阈值进行图像二值化分割后，前景与背景图像的类间方差最大。
"""
ret, thresh = cv2.threshold(img, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

# 显示结果
cv2.imshow('Result', thresh)
cv2.waitKey(0)
cv2.destroyAllWindows()