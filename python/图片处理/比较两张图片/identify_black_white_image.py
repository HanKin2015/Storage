"""
文 件 名: identify_black_white_image.py
文件描述: 识别黑白图片
作    者: HanKin
创建日期: 2023.03.06
修改日期：2023.03.06

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import cv2

def identify_black_white_image_by_diagonal(img_path):
    """0为黑色，255为白色
    只计算对角线
    """
    
    img = cv2.imread(img_path)
    
    # 放大图片大小（效果不是很明显）
    #img = cv2.resize(img, (256, 256))
    #cv2.imwrite("result.png", img)

    gray = cv2.cvtColor(img.copy(), cv2.COLOR_BGR2GRAY)
    
    # 二值化操作
    #ret, thresh = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)

    # 计算图片大小
    imgShape = img.shape
    height = imgShape[0]
    width  = imgShape[1]
    print('imgShape: {}, height: {}, width: {}'.format(imgShape, height, width))
    print('size: {} [32*32*3]'.format(img.size))

    blackNum, whiteNum = 0, 0
    k = height / width
    
    # 只计算了对角线上的点，共64个
    for x in range(width):
        y1 = int(k * x)
        y2 = int((-k) * x + height - 1)
        #print(y1, y2)

        if 0 <= y1 <= (height - 1) and 0 <= y2 <= (height - 1):
            #print(gray[y1][x], gray[y2][x])
            # 第一条对角线
            if gray[y1][x] <= 122:
                blackNum += 1
            else:
                whiteNum += 1
            # 第二条对角线
            if gray[y2][x] <= 122:
                blackNum += 1
            else:
                whiteNum += 1
    print('black count: {}, white count: {}'.format(blackNum, whiteNum))
    if blackNum > whiteNum:
        print("black based image")
    else:
        print("white based image")

def identify_black_white_image(img_path):
    """0为黑色，255为白色
    """
    
    img = cv2.imread(img_path)
    gray = cv2.cvtColor(img.copy(), cv2.COLOR_BGR2GRAY)

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