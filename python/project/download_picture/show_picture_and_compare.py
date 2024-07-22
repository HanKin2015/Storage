# -*- coding: utf-8 -*-
"""
文 件 名: show_picture_and_compare.py
文件描述: 显示图片并比较
备    注：https://cloud.tencent.com/developer/article/2428225
作    者: HanKin
创建日期: 2024.07.22
修改日期：2024.07.22

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time
import requests
from PIL import Image
from io import BytesIO
import psutil
import subprocess
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image, ImageChops
import os
import sys
from skimage.metrics import structural_similarity as compare_ssim
from skimage.metrics import peak_signal_noise_ratio as compare_psnr
import skimage.measure as measure

#伪造浏览器访问
HEADERS = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36',
        }

# 睡眠等待时间
SLEEP_TIME = 2
 
def show_ss_wallpaper():
    """下载图片
    :param init_url: 图片初始地址
    :param save_file_path: 保存目录路径
    :return null
    """
    
    img_url = "http://browser9.qhimg.com/bdr/__85/t01164a798a68fbf958.jpg"
    img_name = "\u6d77\u5e95\u4e16\u754c"
    
    # 使用requests发送get请求
    response = requests.get(url=img_url, headers=HEADERS)
    
    # 检查请求是否成功
    if response.status_code == 200:
        # 使用requests获取图片内容
        img_data = response.content
    
        # 将图片内容转换为文件流
        img_file = BytesIO(img_data)
        # 使用Pillow打开图片
        img = Image.open(img_file)
        
        # 显示图片
        a = np.array(img)
        #plt.ion() #开启interactive mode
        plt.figure(img_name)
        plt.imshow(a)
        #plt.show()
        # 以非阻塞方式显示图形窗口
        plt.show(block=False)
        
        # 关闭显示
        """
        在使用matplotlib.pyplot显示图片时，plt.show()函数会启动一个事件循环，用于处理窗口的交互和事件响应。而time.sleep()函数会阻塞主线程，导致事件循环无法正常运行，从而无法响应打开图片操作。
        """
        #time.sleep(SLEEP_TIME*5)
        plt.pause(3)  # 暂停3秒钟
        plt.close()
        return

        img_Path = 'pictures/' + img_name + '.jpg'
        with open(img_Path, 'wb') as save_img:
            save_img.write(img_data)
    else:
        print("无法获取图片")
    time.sleep(SLEEP_TIME)
    picture_index += 1
    return

def compare_images1(image1_path, image2_path):
    image1 = Image.open(image1_path)
    image2 = Image.open(image2_path)
    
    diff = ImageChops.difference(image1, image2)
    
    if diff.getbbox() is None:
        print("两张图片完全相同")
    else:
        print("两张图片不同")

def compare_images2(image1_path, image2_path):
    image1 = Image.open(image1_path)
    image2 = Image.open(image2_path)
    
    histogram1 = image1.histogram()
    histogram2 = image2.histogram()
    
    print(histogram1)
    print("")
    print(histogram2)
    
    if histogram1 == histogram2:
        print("两张图片完全相同")
    else:
        print("两张图片不同")

def compare_images3(image1_path, image2_path):
    # 读取图片
    image1 = Image.open(image1_path).convert('RGB')
    image2 = Image.open(image2_path).convert('RGB')

    # 将图片转换为灰度图像
    gray_image1 = image1.convert('L')
    gray_image2 = image2.convert('L')

    # 比对两张图片
    diff_image = np.subtract(gray_image1, gray_image2)
    
    print(np.mean(diff_image))

    # 判断是否相同
    threshold = 1.0
    is_same = np.mean(diff_image) < threshold

    return is_same

import cv2

def read_image_with_os_path(image_path):
    """OpenCV在某些情况下对非ASCII字符的支持不完善导致的
    https://docs.pingcode.com/ask/ask-ask/175814.html?p=175814
    """
    
    # 将图片路径转换为绝对路径
    abs_path = os.path.abspath(image_path)

    # 将路径转为系统默认编码，通常为utf-8
    print(type(abs_path))
    if type(abs_path) == str:
        abs_path = abs_path.encode(sys.getfilesystemencoding())


    # 使用cv2.imread读取图片
    image = cv2.imdecode(np.fromfile(abs_path, dtype=np.uint8), cv2.IMREAD_UNCHANGED)
    return image

def compare_images(image1_path, image2_path):
    """
    计算两张图片的结构相似性指标（Structural Similarity Index, SSIM）
    """
    
    # 读取两张图片
    read_image_with_os_path(image2_path)
    image1 = cv2.imread(image1_path)
    image2 = read_image_with_os_path(image2_path)
    
    # 调整图片尺寸为相同大小
    image1 = cv2.resize(image1, (image2.shape[1], image2.shape[0]))

    # 将图片转换为灰度图像
    gray1 = cv2.cvtColor(image1, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.cvtColor(image2, cv2.COLOR_BGR2GRAY)

    # 计算结构相似性指标
    ssim_score, _ = compare_ssim(gray1, gray2, full=True)

    # 打印相似性指标
    print("SSIM score:", ssim_score)

def main():
    """主函数
    """
    
    #show_ss_wallpaper()
    
    # 调用上述函数比较两张图片
    compare_images(r"D:\picture\121.jpg", r"D:\Github\Storage\python\project\download_picture\pictures\兰博基尼.jpg")
    #compare_images(r"D:\picture\39.jpg", r"D:\picture\20.jpg")

def debug():
    """调试
    """

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    

