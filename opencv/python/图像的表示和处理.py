# -*- coding: utf-8 -*-
"""
文 件 名: 图像的表示和处理.py
文件描述: 图像的表示和处理
备    注: 
作    者: HanKin
创建日期: 2025.07.21
修改日期：2025.07.21

Copyright (c) 2025 HanKin. All rights reserved.
"""
import cv2

image = cv2.imread('仓鼠.png')   # 返回一个 NumPy 数组，异常则返回 None

# 显示图像
cv2.imshow("Display Window", image)

# 保存图像
cv2.imwrite("output_image.jpg", image)

# 等待按键输入
cv2.waitKey(0)

# 关闭所有窗口
cv2.destroyAllWindows()