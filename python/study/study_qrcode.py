import qrcode

import qrcode
# 实例化二维码生成类
qr = qrcode.QRCode(
    version=1,
    error_correction=qrcode.constants.ERROR_CORRECT_L,
    box_size=10,
    border=4,
)
# 设置二维码数据
data = "https://www.baidu.com"
qr.add_data(data=data)

# 启用二维码颜色设置
qr.make(fit=True)
img = qr.make_image(fill_color="green", back_color="white")

# 显示二维码
img.show()

# 保存二维码为文件
img.save("baidu.jpg")

import zxing

reader = zxing.BarCodeReader()
barcode = reader.decode("baidu.jpg")
print(barcode.parsed)