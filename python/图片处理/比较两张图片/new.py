# https://blog.csdn.net/fulk6667g78o8/article/details/118409795
# https://blog.csdn.net/jacke121/article/details/79222991
# 一对我以为是正确的，结果还是经不住考验

import cv2
import numpy as np
#import os
 
file1= "other.png"
file2= "white.png"
 
image1 = cv2.imread(file1)
image2 = cv2.imread(file2)
print(type(image1))
print(type(image2))

image1 = cv2.resize(image1, (256, 256))
image2 = cv2.resize(image2, (256, 256))
difference = cv2.subtract(image1, image2)
result = not np.any(difference) #if difference is all zeros it will return False
 
if result is True:
     print("两张图片一样")
else:
     cv2.imwrite("result.jpg", difference)
     print ("两张图片不一样")

print(np.max(difference))

