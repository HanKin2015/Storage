from PIL import Image
from PIL import ImageFilter
import cv2
import time
import os
import numpy as np

test_pic_path = './test.png'
ret_pic_path  = './ret.jpg'
tmp_pic_path  = './tmp.jpg'

# 一个边缘填充的空白像素
write_border = 100

# 执行开始时间
begin_time = time.time()

image = cv2.imdecode(np.fromfile(test_pic_path, dtype=np.uint8), -1)
height, width = image.shape[:2]
print('图像原始大小: {}x{}'.format(height, width))

# 重新调整大小
ret = cv2.resize(image, (height - write_border * 2, width - write_border * 2), interpolation=cv2.INTER_AREA)

# 临时保存一下
cv2.imwrite(tmp_pic_path, ret)

image = Image.open(tmp_pic_path)
gary = image.filter(ImageFilter.DETAIL)

# 增加灰度方便区分
gary = gary.point(lambda i: i*0.9)

img_convert_ndarray = np.array(gary)
height, width = img_convert_ndarray.shape[:2]

print('图像改变后的大小: {}x{}'.format(height, width))

# 边缘填充空白
ret = cv2.copyMakeBorder(img_convert_ndarray, write_border, write_border, write_border, write_border, cv2.BORDER_CONSTANT, value=[255, 255, 255])

# 保存图片
cv2.imencode('.jpg', ret)[1].tofile(ret_pic_path)

# 删除临时图片
os.remove(tmp_pic_path)

end_time = time.time()
print (u'总共耗时：' + str(end_time - begin_time) + 's')
