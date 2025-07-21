import cv2 as cv

img = cv.imread("仓鼠.png")
if img is None:
    print("Error: Could not load image.")
    exit()

cv.imshow("Window", img)
# 注释此行，观察窗口是否自动关闭
#cv.destroyAllWindows()
k = cv.waitKey(0)  # 等待按键

# 添加额外代码，防止程序立即退出
print(f"Pressed key: {k}")
input("Press Enter to exit...")  # 手动确认退出

