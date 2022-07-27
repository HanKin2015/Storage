import cv2
import numpy as np

#调整亮度
filename = "test.png"
img = cv2.imread(filename, 0)
print(np.shape(img))
kernel = np.ones((1,1), np.uint8)
dilate = cv2.dilate(img, kernel, iterations=1)
cv2.imwrite('new_dilate.jpg', dilate)
 
#还有些常用的方法
#cv2.Canny
#cv2.erode
#cv2.rectangle

 
original_img = cv2.imread("test.png", 0)
 
# canny(): 边缘检测
img1 = cv2.GaussianBlur(original_img, (3,3), 0)
canny = cv2.Canny(img1, 50, 150)
 
# 形态学：边缘检测
_, Thr_img = cv2.threshold(original_img, 210, 255, cv2.THRESH_BINARY)#设定红色通道阈值210（阈值影响梯度运算效果）
kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5,5))         #定义矩形结构元素
gradient = cv2.morphologyEx(Thr_img, cv2.MORPH_GRADIENT, kernel) #梯度
 
cv2.imshow("original_img", original_img) 
cv2.imshow("gradient", gradient) 
cv2.imshow('Canny', canny)

input('请输入:')