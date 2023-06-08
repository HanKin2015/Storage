# -*- coding: utf-8 -*-
"""
文 件 名: qrcode_example.py
文件描述: 只能用于生成二维码
作    者: HanKin
创建日期: 2023.06.08
修改日期：2023.06.08

Copyright (c) 2023 HanKin. All rights reserved.
"""

import qrcode
import cv2
import pyzbar.pyzbar
from PIL import Image

def addLogoFunc(img):
    """我们可以为我们的二维码添加Logo，当然Logo尺寸不能过大，否则会影响二维码的识别
    """
    
    icon = Image.open("icon.png")

    img_width, img_height = img.size
    factor = 4
    size_width = int(img_width / factor)
    size_height = int(img_width / factor)

    icon_width, icon_height = icon.size
    if icon_width > size_width or icon_height > size_height:
        icon_width, icon_height = size_width, size_height

    icon = icon.resize((icon_width, icon_height), Image.Resampling.LANCZOS)

    w = int((img_width - icon_width) / 2)
    h = int((img_height - icon_height) / 2)
    img.paste(icon, (w, h), icon)


if __name__ == "__main__":
    qr = qrcode.QRCode(
        version=2,
        #  version：二维码的格子矩阵大小，可以是1到40,1最小为21*21,40是177*177
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        #  error_correction：二维码错误容许率，默认 ERROR_CORRECT_M，容许小于 15% 的错误率
        box_size=15,
        #  box_size：二维码每个小格子包含的像素数量
        border=3
        #  border：二维码到图片边框的小格子数，默认值为 4
    )

    # 二维码内容（链接地址或文字）
    data = '我是仿真器，我是个大傻逼'
    qr.add_data(data=data)
    # 启用二维码颜色设置
    qr.make(fit=True)
    img = qr.make_image(fill_color='green', back_color='white')
    # 增加图标 addLogoFunc
    addLogoFunc(img)
    # 显示二维码
    img.show()
    # 保存二维码
    img.save('qrcode.jpg')
    
    # 读取图像
    img = cv2.imread('qrcode.jpg')

    # 使用pyzbar库识别二维码
    decoded_objects = pyzbar.pyzbar.decode(img)

    # 显示识别结果
    for obj in decoded_objects:
        print("二维码内容：", obj.data.decode("utf-8"))
