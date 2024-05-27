# -*- coding: utf-8 -*-
"""
文 件 名: pyzbar_example.py
文件描述: https://github.com/skb666/ZBarWin64/blob/master/x64/Release/libzbar-64.dll
备    注：https://blog.csdn.net/qq_45280030/article/details/126148328
作    者: HanKin
创建日期: 2024.05.24
修改日期：2024.05.24

Copyright (c) 2024 HanKin. All rights reserved.
"""
import cv2
import pyzbar.pyzbar as pyzbar

img = cv2.imread(r"D:\Github\Storage\qt\python\office_assistant\src\barcode.png")
cv2.imshow("img", img)
cv2.waitKey(0)
gray = cv2.cvtColor(img, cv2.COLOR_RGBA2GRAY)
barcodes = pyzbar.decode(gray)
for barcode in barcodes:
    print(barcode.data.decode('utf-8'))