# -*- coding: utf-8 -*-
"""
文 件 名: compare_two_picture.py
文件描述: 比较两张图片
备    注: https://blog.csdn.net/qq_38641985/article/details/118304624
作    者: HanKin
创建日期: 2023.02.28
修改日期：2023.02.28

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
from PIL import Image
from PIL import ImageChops
import math
import operator
from functools import reduce
import cv2
import numpy as np

# 计算单通道的直方图的相似值
def calculate1(path_one, path_two):
    image1 = cv2.imread(path_one)  
    image2 = cv2.imread(path_two)
    hist1 = cv2.calcHist([image1], [0], None, [256], [0.0, 255.0])
    hist2 = cv2.calcHist([image2], [0], None, [256], [0.0, 255.0])
    # 计算直方图的重合度
    degree = 0
    for i in range(len(hist1)):
        if hist1[i] != hist2[i]:
            degree = degree + (1 - abs(hist1[i] - hist2[i]) / max(hist1[i], hist2[i]))
        else:
            degree = degree + 1
    print(degree, len(hist1))
    degree = degree / len(hist1)
    print('单通道的直方图算法相似度：', degree)
    return degree

def compare_images1(path_one, path_two, diff_save_location):
    image_one = Image.open(path_one)
    image_two = Image.open(path_two)
    try: 
        diff = ImageChops.difference(image_one, image_two)
        if diff.getbbox() is None:
        # 图片间没有任何不同则直接退出
            print("We are the same!")
        else:
            diff.save(diff_save_location)
    except ValueError as e:
        text = ("表示图片大小和box对应的宽度不一致")
        print("【{0}】{1}".format(e,text))

def compare_images2(pic1, pic2):
    image1 = Image.open(pic1)
    image2 = Image.open(pic2)
    histogram1 = image1.histogram()
    histogram2 = image2.histogram()
    differ = math.sqrt(reduce(operator.add, list(map(lambda a,b: (a-b)**2,histogram1, histogram2)))/len(histogram1))
    print('differ:',differ)
    if differ == 0:
        return 'same'
    else:
        return 'diff'

# Hash值对比
def cmpHash(hash1, hash2,shape=(10,10)):
    n = 0
    # hash长度不同则返回-1代表传参出错
    if len(hash1)!=len(hash2):
        return -1
    # 遍历判断
    for i in range(len(hash1)):
        # 相等则n计数+1，n最终为相似度
        if hash1[i] == hash2[i]:
            n = n + 1
    return n/(shape[0]*shape[1])
# 均值哈希算法
def aHash(img,shape=(10,10)):
    # 缩放为10*10
    img = cv2.resize(img, shape)
    # 转换为灰度图
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # s为像素和初值为0，hash_str为hash值初值为''
    s = 0
    hash_str = ''
    # 遍历累加求像素和
    for i in range(shape[0]):
        for j in range(shape[1]):
            s = s + gray[i, j]
    # 求平均灰度
    avg = s / 100
    # 灰度大于平均值为1相反为0生成图片的hash值
    for i in range(shape[0]):
        for j in range(shape[1]):
            if gray[i, j] > avg:
                hash_str = hash_str + '1'
            else:
                hash_str = hash_str + '0'
    return hash_str

# 通过得到RGB每个通道的直方图来计算相似度
def classify_hist_with_split(image1, image2, size=(256, 256)):
    # 将图像resize后，分离为RGB三个通道，再计算每个通道的相似值
    image1 = cv2.resize(image1, size)
    image2 = cv2.resize(image2, size)
    sub_image1 = cv2.split(image1)
    sub_image2 = cv2.split(image2)
    sub_data = 0
    for im1, im2 in zip(sub_image1, sub_image2):
        sub_data += calculate(im1, im2)
    sub_data = sub_data / 3
    return sub_data


# 计算单通道的直方图的相似值
def calculate(image1, image2):
    hist1 = cv2.calcHist([image1], [0], None, [256], [0.0, 255.0])
    hist2 = cv2.calcHist([image2], [0], None, [256], [0.0, 255.0])
    # 计算直方图的重合度
    degree = 0
    for i in range(len(hist1)):
        if hist1[i] != hist2[i]:
            degree = degree + (1 - abs(hist1[i] - hist2[i]) / max(hist1[i], hist2[i]))
        else:
            degree = degree + 1
    degree = degree / len(hist1)
    return degree

def main():
    """主函数
    """
    
    calculate1('not_all_black.png', 'black_screen.png')
    # 这两张明显相同，居然结果有90以上不同，说明该函数不准确
    compare_images1('all_black.png', 'what.png', 'save_diff.png')
    compare_images2('all_black.png', 'what.png')
    
    img1 = cv2.imread('error_screen.png')  
    img2 = cv2.imread('black_screen.png')

    hash1 = aHash(img1)
    hash2 = aHash(img2)
    n = cmpHash(hash1, hash2)
    print('均值哈希算法相似度：', n)

    n = classify_hist_with_split(img1, img2, (32, 32))
    print('三直方图算法相似度：', n)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    
    
    
    
    



