from PIL import Image
import pytesseract

image = Image.open("test.jpg") #打开图片
#print(image.size) #测试图片像素尺寸
text = pytesseract.image_to_string(image, lang='chi_sim') #图片转字符串
text = text.replace("“ ","").replace("。","") #去掉杂质，提纯
print(text) #测试结果