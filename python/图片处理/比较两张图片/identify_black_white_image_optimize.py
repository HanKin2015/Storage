"""
文 件 名: identify_black_white_image_optimize.py
文件描述: 优化打包大小，未优化为241MB，优化完后241MB，没效果
作    者: HanKin
创建日期: 2023.03.06
修改日期：2023.03.06

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
from cv2 import imread, cvtColor, COLOR_BGR2GRAY

def identify_black_white_image(img_path):
    """0为黑色，255为白色
    """
    
    img = imread(img_path)
    gray = cvtColor(img.copy(), COLOR_BGR2GRAY)

    # 计算图片大小
    imgShape = img.shape
    height = imgShape[0]
    width  = imgShape[1]
    print('imgShape: {}, height: {}, width: {}'.format(imgShape, height, width))
    print('size: {} [32*32*3]'.format(img.size))

    # 黑白判断阈值
    black_threshold = [0, 9]
    white_threshold = [246, 255]
    light_white_threshold = [236, 245]

    black_count, white_count, light_white_count = 0, 0, 0
    print(gray[0][0])
    for x in range(width):
        for y in range(height):
            #print(gray[x][y])
            if black_threshold[0] <= gray[x][y] and gray[x][y] <= black_threshold[1]:
                black_count += 1
            if white_threshold[0] <= gray[x][y] and gray[x][y] <= white_threshold[1]:
                white_count += 1
            if light_white_threshold[0] <= gray[x][y] and gray[x][y] <= light_white_threshold[1]:
                light_white_count += 1
    print('black count: {}, white count: {}, light white count: {}'.format(black_count, white_count, light_white_count))
    max_value = max(black_count, white_count, light_white_count)
    print('max value: {}'.format(max_value))

def main():
    """主函数
    """
    
    img_path = 'black_screen.png'
    identify_black_white_image(img_path)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))