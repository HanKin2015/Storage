import cv2
import numpy as np

# 读取图像
img = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)

# 定义 Sobel 滤波器
sobel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
sobel_y = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])

# 对图像进行卷积操作
img_sobel_x = cv2.filter2D(img, -1, sobel_x)
img_sobel_y = cv2.filter2D(img, -1, sobel_y)

# 将两个卷积结果合并
img_sobel = cv2.addWeighted(img_sobel_x, 0.5, img_sobel_y, 0.5, 0)

# 显示结果
cv2.imshow('Original Image', img)
cv2.imshow('Sobel Filtered Image', img_sobel)
cv2.waitKey(0)
cv2.destroyAllWindows()
