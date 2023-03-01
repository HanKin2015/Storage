# -*- coding: utf-8 -*-
"""
文 件 名: compare_two_picture.py
文件描述: 比较两张图片
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

def main():
    """主函数
    """

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
    
    
    
    
    



