"""
屏幕截图里识别数字, 非常正规的白色字体,图片背景略微复杂, 但是识别率不高, 实在无法相信知名软件包居然是这个效果, 反复找资料实验后发现: 图像要 白底黑字  白底黑字  白底黑字  重要的事情说三遍, 凡是没有白底黑字的也能识别,但是效果惨不忍睹,正确率低于40%

tesseract要想识别中文的概率达到百分之七十以上，首先要字体是宋体；其次背景要很干净，没有跨行。 因为只安装了中文简体的包，没有安繁体，而繁体是chi_tra
"""

import cv2
import pytesseract
import numpy as np

rawImage = cv2.imread('./test.png')
height, width, deep = rawImage.shape                 # cropImg是从图片里截取的,只包含一行数字
gray = cv2.cvtColor(rawImage, cv2.COLOR_BGR2GRAY)      # 转灰度图
dst = np.zeros((height, width, 1), np.uint8)        
for i in range(0, height):                          # 反相 转白底黑字
    for j in range(0, width):
        grayPixel = gray[i, j]
        dst[i, j] = 255 - grayPixel
ret, canny = cv2.threshold(dst, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)   # 二值化
# psm 7表示单行文字,单个字符psm 10, tessedit_char_whitelist 限定只有数字
#text = pytesseract.image_to_string(canny , config='--psm 7 --oem 3 -c tessedit_char_whitelist=0123456789')
#print("文字识别", text)

string = pytesseract.image_to_string(canny, lang="eng", config="--psm 7")
print(string)