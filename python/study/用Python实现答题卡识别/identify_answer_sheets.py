# -*- coding: utf-8 -*-
"""
文 件 名: identify_answer_sheets.py
文件描述: 用Python实现答题卡识别
备    注: https://mp.weixin.qq.com/s/DFK-qzIWzo8w5ZLzmzxMpA
作    者: HanKin
创建日期: 2023.11.28
修改日期：2023.11.28

Copyright (c) 2023 HanKin. All rights reserved.
"""
import cv2
import numpy as np
import imshow
import matplotlib.pyplot as plt 

img = cv2.imread("1.png",1)

# 高斯去噪
img_gs = cv2.GaussianBlur(img,[5,5],0)
# 转灰度
img_gray = cv2.cvtColor(img_gs,cv2.COLOR_BGR2GRAY)
# 自适应二值化
_, binary_img = cv2.threshold(img_gray, 0, 255, cv2.THRESH_OTSU | cv2.THRESH_BINARY)

# 找轮廓
contours, hierarchy = cv2.findContours(binary_img,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)
# 按照轮廓的面积从大到小排序
cnts = sorted(contours,key = cv2.contourArea,reverse=True)
# 画轮廓
draw_img = cv2.drawContours(img.copy(),cnts[0],-1,(0,255,255),2)

# 轮廓近似
# 阈值，一般为轮廓长度的2%
alpha = 0.02*cv2.arcLength(cnts[0],True)
approxCurve = cv2.approxPolyDP(cnts[0],alpha,True)
draw_img = cv2.drawContours(img.copy(),[approxCurve],-1,(255,0,0),2)

#透视变换
# 矩形的四个顶点为approxCurve[0][0],approxCurve[1][0],approxCurve[2][0],approxCurve[3][0]
# 分别表示矩形的TL,BL,BR,TR四个点
a1 = list(approxCurve[0][0])
a2 = list(approxCurve[1][0])
a3 = list(approxCurve[2][0])
a4 = list(approxCurve[3][0])
# 原始矩阵
mat1 = np.array([a1,a2,a3,a4],dtype = np.float32)

# 计算矩形的w和h
w1 = int(np.sqrt((a1[0]-a4[0])**2+(a1[1]-a4[1])**2))
w2 = int(np.sqrt((a2[0]-a3[0])**2+(a2[1]-a3[1])**2))
h1 = int(np.sqrt((a1[0]-a2[0])**2+(a1[1]-a2[1])**2))
h2 = int(np.sqrt((a3[0]-a4[0])**2+(a3[1]-a4[1])**2))
w,h=max(w1,w2),max(h1,h2)
# 计算透视变换后的坐标
new_a1 = [0,0]
new_a2 = [0,h]
new_a3 = [w,h]
new_a4 = [w,0]
# 目标矩阵
mat2 = np.array([new_a1,new_a2,new_a3,new_a4],dtype = np.float32)
# 透视变换矩阵
mat = cv2.getPerspectiveTransform(mat1,mat2)
# 进行透视变换
res = cv2.warpPerspective(img,mat,(w,h))
plt.imshow((res))
plt.show()

res_gray = cv2.cvtColor(res,cv2.COLOR_BGR2GRAY)
_,binary_res = cv2.threshold(res_gray,0,255,cv2.THRESH_OTSU|cv2.THRESH_BINARY_INV)
contours = cv2.findContours(binary_res,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_NONE)[0]
dst = cv2.drawContours(res.copy(),contours,-1,(0,0,255),1)
plt.imshow(dst)
plt.show()

# 挑选合适的轮廓
def check(contours):
    ans = []
    for i in contours:
        area = float(cv2.contourArea(i))
        length = float(cv2.arcLength(i,True))
        if area<=0 or length<=0:
            continue
        if area/length >7.05 and area/length<10.5:
            ans.append(i)
    return ans
ans_contours = check(contours)
dst_new = cv2.drawContours(res.copy(),ans_contours,-1,(0,255,255),3  )
plt.imshow(dst_new)
plt.show()

# 遍历每一个圆形轮廓，画外接圆
circle = []
for i in ans_contours:
    (x,y),r = cv2.minEnclosingCircle(i)
    center = (int(x),int(y))
    r = int(r)
    circle.append((center,r))
# 按照外接圆的水平坐标排序center[1]，也就是圆心的高度h，或者y坐标
circle.sort(key = lambda x:x[0][1])
A = []
for i in range(1,6):
    now = circle[(i-1)*5:i*5]
    now.sort(key = lambda x:x[0][0])
    A.extend(now)

def dots_distance(dot1,dot2):
    #计算二维空间中两个点的距离
    return ((dot1[0]-dot2[0])**2+(dot1[1]-dot2[1])**2)**0.5
def count_dots(center,radius):
    #输入圆的中心点与半径，返回圆内所有的坐标
    dots = []
    for i in range(-radius,radius+1):
        for j in range(-radius,radius+1):
            dot2 = (center[0]+i,center[1]+j)
            if dots_distance(center,dot2) <= radius:
                dots.append(dot2)
    return dots
 
da = []
for i in A:
    dots = count_dots(i[0],i[1])
    all_dots = len(dots)
    whilt_dots = 0
    for j in dots:
        if binary_res[j[1]][j[0]] == 255:
            whilt_dots = whilt_dots+1
    if whilt_dots/all_dots>=0.4:
        da.append(1)
    else:
        da.append(0)
da = np.array(da)
da = np.reshape(da,(5,5))

print(da)