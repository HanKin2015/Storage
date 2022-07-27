from PIL import Image
import pytesseract

# 识别图片中的文字。对图片进行灰度、二化值处理
def get_picture_str(picturePath):
    ## 图片灰度处理
    picture = Image.open(picturePath).convert('L')  

    ## 二值化，采用阈值分割法，threshold为分割点
    threshold = 200
    table = []
    for j in range(256):
        if j < threshold:
            table.append(0)
        else:
            table.append(1)
    newPicture = picture.point(table, '1')

    ## 保存的时候调整屏幕分辨率为300，有利于 tesseract 识别
    newPicture.save(picturePath, dpi=(300.0,300.0)) 

    ## 识别
    text=pytesseract.image_to_string(Image.open(picturePath) ,lang='chi_sim')   
    return text
    
print(get_picture_str('./original.png'))