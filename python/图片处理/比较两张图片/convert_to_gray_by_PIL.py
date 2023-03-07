"""
文 件 名: convert_to_gray_by_PIL.py
文件描述: 实现彩色图像转为灰度图像，来替代cv2库
备    注: https://blog.csdn.net/qq_44368508/article/details/126419058
作    者: HanKin
创建日期: 2023.03.07
修改日期：2023.03.07

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
from PIL import Image
from matplotlib import pyplot as plt
import numpy as np

def show_image_from_array(gray_img_array):
    """从图片数组数据中显示图片
    """
    
    gray_img = Image.fromarray(np.uint8(gray_img_array))
    print_res = 'gray'
    plt.figure('DS')
    #plt.figure(num=1, figsize=(8,5),)
    plt.imshow(gray_img, cmap='gray')
    # 命名标题
    plt.title(print_res)
    # 不显示坐标轴
    plt.axis('off')
    plt.show()

def convert_to_gray_by_PIL(img_path):
    """0为黑色，255为白色
    """
    
    color_img = Image.open(img_path)
    # 转换成灰度图像
    gray_img = color_img.convert('L')
    print(type(gray_img))
    
    # PIL中的Image转化为数组array
    gray_img_array = np.asarray(gray_img)
    print(type(gray_img_array), gray_img_array.shape)
    show_image_from_array(gray_img_array)

    # 计算图片大小
    imgShape = gray_img_array.shape
    height = imgShape[0]
    width  = imgShape[1]
    print('imgShape: {}, height: {}, width: {}'.format(imgShape, height, width))
    print('size: {} [32*32*3]'.format(gray_img_array.size))

    # 黑白判断阈值
    black_threshold = [0, 9]
    white_threshold = [246, 255]
    light_white_threshold = [236, 245]

    black_count, white_count, light_white_count = 0, 0, 0
    print('gray_img_array[0][0]: {}'.format(gray_img_array[0][0]))
    for x in range(width):
        for y in range(height):
            if gray_img_array[x][y] < 40:
                print(gray_img_array[x][y])
            if black_threshold[0] <= gray_img_array[x][y] and gray_img_array[x][y] <= black_threshold[1]:
                black_count += 1
            if white_threshold[0] <= gray_img_array[x][y] and gray_img_array[x][y] <= white_threshold[1]:
                white_count += 1
            if light_white_threshold[0] <= gray_img_array[x][y] and gray_img_array[x][y] <= light_white_threshold[1]:
                light_white_count += 1
    print('black count: {}, white count: {}, light white count: {}'.format(black_count, white_count, light_white_count))
    max_value = max(black_count, white_count, light_white_count)
    print('max value: {}'.format(max_value))

def main():
    """主函数
    """
    
    img_path = 'other.png'
    convert_to_gray_by_PIL(img_path)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))