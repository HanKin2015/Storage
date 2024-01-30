# -*- coding: utf-8 -*-
"""
文 件 名: del_watermark.py
文件描述: 去除水印，使用工具并不能达到需求
备    注: https://baijiahao.baidu.com/s?id=1763944428348365954&wfr=spider&for=pc
作    者: HanKin
创建日期: 2024.01.29
修改日期：2024.01.29

Copyright (c) 2024 HanKin. All rights reserved.
"""
import poimage
import cv2
import numpy as np
from itertools import product
from PIL import Image

input_img_path = r'D:\Demo\aDesk_Tools\additional_data\static\device_helper_picture_en\bulkCacheListQuirk.png'
output_img_path= 'xxx.png'
no_watermark_img_path = 'aaa.png'
    
def del_watermark1():
    """使用第三方库
    效果非常差
    """
    poimage.del_watermark(input_image=input_img_path, output_image=output_img_path)

def del_watermark2():
    img = cv2.imread(input_img_path)
    new = np.clip(1.4057577998008846*img-38.33089999653017, 0, 255).astype(np.uint8)
    cv2.imshow('a.png', new)
    cv2.waitKey(0)
    cv2.imwrite(output_img_path, new)

def del_watermark3():
    """替换数值
    需要背景是同一个颜色，不满足需求
    https://zhuanlan.zhihu.com/p/420294959?utm_id=0
    """
    img = Image.open(input_img_path)
    width, height = img.size
    for pos in product(range(width), range(height)):
        if sum(img.getpixel(pos)[:3]) > 400:
            img.putpixel(pos, (255,255,255))
    img.save(output_img_path)

def del_watermark4():
    """指定范围去除水印进行图像融合
    缺点很明显，需要无水印图片，其实就是复制粘贴
    难受，发现使用画图软件手动融合拼接速度更快
    https://pythonjishu.com/yzscjgbwxbvjhbp/
    """
    # 读入原始图片和带有水印的图片
    img1 = cv2.imread(no_watermark_img_path)
    img2 = cv2.imread(input_img_path)
    
    print(img1.shape, img2.shape)

    # 调整图片尺寸
    img1 = cv2.resize(img1, (img2.shape[1], img2.shape[0]))

    # 提取感兴趣区域
    roi1 = img1[480:526, 680:724]
    roi2 = img2[480:526, 680:724]

    # 图像融合
    alpha = 1
    beta = 1 - alpha
    dst = cv2.addWeighted(roi1, alpha, roi2, beta, 0)

    # 将处理后的图像保存
    img2[480:526, 680:724] = dst
    cv2.imwrite(output_img_path, img2)

def del_watermark5():
    """和del_watermark4()方法一样
    """
    # 读入原始图片和带有水印的图片
    img1 = Image.open(r'image1.jpg')
    img2 = Image.open(r'image2.jpg')

    # 调整图片尺寸
    img1 = img1.resize((img2.size[0], img2.size[1]))

    # 提取感兴趣区域
    box = (300, 400, 700, 800)
    roi1 = img1.crop(box)
    roi2 = img2.crop(box)

    # 图像粘贴
    img2.paste(roi1, box)

    # 将处理后的图像保存
    img2.save('result.jpg')

def del_watermark6():
    """失败了
    https://www.python100.com/html/79234.html
    """
    img = cv2.imread(no_watermark_img_path)
    mask = cv2.imread(input_img_path, 0)

    dst = cv2.inpaint(img, mask, 3, cv2.INPAINT_TELEA)
    cv2.imwrite(output_img_path, dst)

if __name__ == '__main__':
    del_watermark4()
