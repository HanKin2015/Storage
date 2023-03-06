"""
这个示例代码使用了OpenCV和v4l2库，首先打开了视频设备/dev/video0，然后设置了视频格式为640x480的YUYV格式。
最后，使用一个循环不断捕获视频帧并显示在窗口中，直到用户按下q键退出程序。
"""

import cv2
import v4l2

# 打开视频设备
cap = cv2.VideoCapture("/dev/video0")

# 设置视频格式
fmt = v4l2.v4l2_format()
fmt.type = v4l2.V4L2_BUF_TYPE_VIDEO_CAPTURE
fmt.fmt.pix.width = 640
fmt.fmt.pix.height = 480
fmt.fmt.pix.pixelformat = v4l2.V4L2_PIX_FMT_YUYV
fmt.fmt.pix.field = v4l2.V4L2_FIELD_NONE
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'YUYV'))
cap.set(cv2.CAP_PROP_FRAME_WIDTH, fmt.fmt.pix.width)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, fmt.fmt.pix.height)

# 开始捕获视频
while True:
    ret, frame = cap.read()
    if not ret:
        break
    cv2.imshow("frame", frame)
    if cv2.waitKey(1) == ord('q'):
        break

# 释放资源
cap.release()
cv2.destroyAllWindows()