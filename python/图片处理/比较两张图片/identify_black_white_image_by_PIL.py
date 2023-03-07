"""
文 件 名: identify_black_white_image_by_PIL.py
文件描述: 直接通过PIL判断图片的大体颜色范围
备    注: https://blog.csdn.net/weixin_41956627/article/details/128142059
作    者: HanKin
创建日期: 2023.03.07
修改日期：2023.03.07

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
from PIL import Image 
#from PIL import ImageChops

def identify_black_white_image_by_PIL(img_path):
    """0为黑色，255为白色
    """
    
    print('{}:'.format(img_path))
    color_img = Image.open(img_path)
    #print(color_img.getbbox())  # 全黑为None，不全黑为(0, 0, 32, 32)
    #print(ImageChops.invert(color_img).getbbox())   # 反转，全白为None，不全白为(0, 0, 32, 32)
    
    # 转换成灰度图像
    gray_img = color_img.convert('L')
    #print(type(gray_img))
    
    # 图像中的最高和最低值
    extrema = gray_img.getextrema()
    print(type(extrema), extrema)
    
    # 先将图像转换为灰度模式，否则，极值可能是RGB或RGBA元组，或者是单个灰度值或索引
    #print(color_img.getextrema())
    
    # 返回一个（count，color）元组的无序list，其中count是对应颜色在图像中出现的次数
    #clrs = color_img.getcolors()
    #clrs = Image.Image.getcolors(color_img)
    #print(clrs)
    
    #print(len(extrema))
    
    # 黑白判断阈值
    black_threshold = (0, 9)
    white_threshold = (246, 255)
    light_white_threshold = (236, 245)
    #print(type(black_threshold))

    if black_threshold[0] <= extrema[0] and extrema[1] <= black_threshold[1]:
        return 'black'
    if white_threshold[0] <= extrema[0] and extrema[1] <= white_threshold[1]:
        return 'white'
    if light_white_threshold[0] <= extrema[0] and extrema[1] <= light_white_threshold[1]:
        return 'light white'
    return 'not in range'

def main():
    """主函数
    """
    
    img_path = 'image/other.png'
    identify_black_white_image_by_PIL(img_path)
    identify_black_white_image_by_PIL('image/black_screen.png')
    identify_black_white_image_by_PIL('image/error_screen.png')
    identify_black_white_image_by_PIL('image/little_black.png')
    identify_black_white_image_by_PIL('image/white.png')

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))