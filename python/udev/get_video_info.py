"""
文 件 名: get_video_info.py
文件描述: 想获取video的分辨率然而失败了
作    者: HanKin
创建日期: 2021.08.16
修改日期：2021.08.16

Copyright (c) 2021 HanKin. All rights reserved.
"""

import cv2
import time

def decode_fourcc(cc):
    return "".join([chr((int(cc) >> 8 * i) & 0xFF) for i in range(4)])
 
cap = cv2.VideoCapture(0)               # 创建capture对象
#cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920) # 设置宽度
#cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)# 设置高度
 
#cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('M', 'J', 'P', 'G'))
fps = cap.get(cv2.CAP_PROP_FPS) #获取视频帧数
print("fps: ", fps)
print("isOpened: ", cap.isOpened())

frame_width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)     # 获取宽度
frame_height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)   # 获取高度

print("frame: {:.0f}x{:.0f}".format(frame_width, frame_height))
print("format: ", cap.get(cv2.CAP_PROP_FORMAT))
print("pos: ", cap.get(cv2.CAP_PROP_POS_MSEC))
print("format: ", cap.get(cv2.CAP_PROP_FOURCC), decode_fourcc(cap.get(cv2.CAP_PROP_FOURCC)))
print(dir(cv2.CAP_PROP_FOURCC))
#print(help(cv2))
#print(dir(cv2))

while False:
    ret, frame = cap.read()
 
    cv2.imshow("打开摄像头", frame)
 
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
    if cv2.waitKey(1) & 0xFF == ord('q'):   # 点击q键退出
        break
 
cap.release()
cv2.destroyAllWindows()