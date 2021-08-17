import cv2
import time
 
cap = cv2.VideoCapture(0)               # 创建capture对象
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920) # 设置宽度
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1080)# 设置高度
 
cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter.fourcc('M', 'J', 'P', 'G'))
 
while True:
    ret, frame = cap.read()
 
    cv2.imshow("打开摄像头", frame)
 
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
    if cv2.waitKey(1) & 0xFF == ord('q'):   # 点击q键退出
        break
 
cap.release()
cv2.destroyAllWindows()