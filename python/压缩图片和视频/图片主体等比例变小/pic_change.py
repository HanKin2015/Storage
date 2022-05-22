from PIL import Image
from PIL import ImageFilter
import cv2
import time
import os
import numpy as np
im = Image.new("RGB", (400, 400), "white")
imndarray = np.array(im)


path = "./original"
path1 = "./changed"
filenames = os.listdir(path)

begin_time = time.time()
#读入图像
#resp = urllib.request.urlopen(url)
#image = np.asarray(bytearray(resp.read()), dtype="uint8")
#image = cv2.imdecode(image, cv2.IMREAD_COLOR)
for i in filenames:
    filename = os.path.join(path, i)
    filename1 = os.path.join(path1, i)
    image = cv2.imdecode(np.fromfile(filename, dtype=np.uint8), -1)
    #双三次插值
    height, width = image.shape[:2]  #获取原图像的水平方向尺寸和垂直方向尺寸。
    print("原始图像大小: {}x{}".format(height, width))

    # 变成正方形图片
    new_size = 400
    temp = max(height, width)
    multemp = temp/400
    if height > width:
        res = cv2.resize(image, (int(width / multemp), 400), interpolation=cv2.INTER_AREA)
    elif height < width:
        res = cv2.resize(image, (400, int(height / multemp)), interpolation=cv2.INTER_AREA)
    else:
        res = cv2.resize(image, (400, 400), interpolation=cv2.INTER_AREA)
    
    cv2.imwrite("./ret.jpg", res)
    imgE = Image.open("./ret.jpg")
    gary2 = imgE.filter(ImageFilter.DETAIL)
    
    #图像点运算
    gary3 = gary2.point(lambda i: i*0.9)
    #savePath = (filename1)
    img_convert_ndarray = np.array(gary3)
    height1, width1 = img_convert_ndarray.shape[:2]

    print(height1, width1)
    height1 = 300
    width1 = 300

    temph = int((400 - height1)/2)
    tempw = int((400 - width1)/2)

    print(temph, tempw, 400-temph-height1, 400-tempw-width1)

    #a = cv2.copyMakeBorder(img_convert_ndarray, temph, 400-temph-height1, tempw, 400-tempw-width1, cv2.BORDER_CONSTANT, value=[255, 255, 255])
    a = cv2.copyMakeBorder(img_convert_ndarray, 100, 100, 100, 100, cv2.BORDER_CONSTANT, value=[255, 255, 255])
    cv2.imencode('.jpg', a)[1].tofile(filename1)  # 保存图片

end_time = time.time()
print (u'总共耗时：' + str(end_time - begin_time) + 's')
