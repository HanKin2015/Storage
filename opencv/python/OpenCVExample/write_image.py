# 导入 OpenCV 库
import cv2

# 1. 读取图像
# 替换为实际的图像路径，这里是当前目录下的 "bird.jpg"
image_path = "./仓鼠.png"
image = cv2.imread(image_path)

# 检查图像是否成功读取
if image is None:
    print("错误：无法加载图像，请检查路径是否正确。")
    exit()

# 2. 显示图像
# 创建一个名为 "Display Image" 的窗口，并在其中显示图像
cv2.imshow("Display Image", image)

# 3. 等待用户按键
# 参数 0 表示无限等待，直到用户按下任意键
key = cv2.waitKey(0)

# 4. 根据用户按键执行操作
if key == ord('s'):  # 如果按下 's' 键
    # 保存图像
    output_path = "saved_image.jpg"
    cv2.imwrite(output_path, image)
    print(f"图像已保存为 {output_path}")
else:  # 如果按下其他键
    print("图像未保存。")

# 5. 关闭所有窗口
#cv2.destroyAllWindows()