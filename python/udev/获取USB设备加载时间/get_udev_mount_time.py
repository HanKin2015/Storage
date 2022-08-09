# -*- coding: utf-8 -*-
"""
文 件 名: get_udev_mount_time.py
文件描述: 获取USB设备加载时间
作    者: HanKin
创建日期: 2022.07.28
修改日期：2022.08.02

Copyright (c) 2022 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger
import usb
from usb.core import USBError
import usb.backend.libusb0
import usb.backend.libusb1
import os
import tkinter as tk

def main():
    wmi = win32com.client.GetObject ("winmgmts:")
    for usb in wmi.InstancesOf ("Win32_USBHub"):
       logger.info(usb.DeviceID)

    print()

    for usb in wmi.InstancesOf ("win32_usbcontrollerdevice"):
        logger.info(usb.Dependent)


def test():
    libusb_dll_path = os.getcwd()+'/libusb-1.0.dll'
    logger.info('libusb_dll_path: {}'.format(libusb_dll_path))
    if not os.path.exists(libusb_dll_path):
        logger.error('libusb dll file not exists')
        #return
    
    # 为啥不能直接写成字符串(注意libusb1加载1.dll，不能错位)
    backend = usb.backend.libusb1.get_backend(find_library=lambda x: libusb_dll_path)
    
    logger.info(usb.core.show_devices(backend=backend))
    devices = usb.core.find(find_all=True, backend=backend)
    
    while True:
        try:
            # 获得下一个值:
            dev = next(devices)
            logger.info('iManufacturer   : %s' %usb.util.get_string(dev, 256, 1))
            logger.info('iProduct            : %s' %usb.util.get_string(dev, 256, 2))
            logger.info('iSerialNumber   : %s' %usb.util.get_string(dev.dev, 256, 3))
            print("device bus:", dev.bus)
            print("device address:", dev.address)
            print("device port:", dev.port_number)
            print("device speed:", dev.speed)
        except StopIteration:
            # 遇到StopIteration就退出循环
            break
    logger.info('test is over')

def debug():
    libusb_dll_path = os.getcwd()+'/libusb-1.0.dll'
    logger.info('libusb_dll_path: {}'.format(libusb_dll_path))
    if not os.path.exists(libusb_dll_path):
        logger.error('libusb dll file not exists')
        #return
    
    # 为啥不能直接写成字符串
    #backend = usb.backend.libusb0.get_backend(find_library=lambda x: libusb_dll_path)
    #backend = usb.backend.libusb0.get_backend(find_library=lambda x: 'D:\\Github\\Storage\\python\\udev\\U盘自动拷贝\\libusb\\amd64\\libusb0.dll')
    #print(backend)
    print(usb.backend.libusb0.get_backend())
    print(usb.backend.libusb1.get_backend())
    backend = usb.backend.libusb1.get_backend()
    
    #logger.info(list(usb.core.find(find_all=True)))
    #logger.info(get_usb_devices(backend))
    devices = list(usb.core.find(find_all=True))
    if devices:
        logger.info(len(devices))
        logger.info(type(devices[0]))
    
    for device in devices:
        #print(str(device))
        #device.set_configuration()
        pass

    vendor_id = 0x8086
    product_id = 0x7020
    
    print(usb.core.show_devices())
    dev = usb.core.find(idVendor=vendor_id, idProduct=product_id)
    if dev is None:
        raise ValueError('Device not found')
    print(dev)
    return
    
    protocol = 'USB2.0'
    busses = usb.busses()
    logger.info('type(busses): {}'.format(type(busses)))
    for bus in busses:
        #logger.info('len(bus.devices): {}'.format(len(bus.devices)))
        for dev in bus.devices:
            #logger.info('dev idVendor: {}, idProduct: {}'.format(dev.idVendor, dev.idProduct))
            if dev.idVendor == vendor_id and dev.idProduct == product_id:
                logger.info('Test vehicle %s device FOUND!' %protocol)
                logger.info('iManufacturer   : %s' %usb.util.get_string(dev.dev, 256, 1))
                logger.info('iProduct            : %s' %usb.util.get_string(dev.dev, 256, 2))
                logger.info('iSerialNumber   : %s' %usb.util.get_string(dev.dev, 256, 3))
                return dev
    logger.info('Test vehicle %s device NOT FOUND!' %protocol)

#图库引用
from PIL import Image
#识别库引用
import pytesseract as pt
#图形界面引用
import tkinter as tk
#路径引用
import tkinter.filedialog as filedialog
class Application(tk.Tk):
    """
    图形界面应用
    """
    
    def __init__(self):
        super().__init__()
        self.title("获取USB设备加载时间")

        # r"" 的作用是去除转义字符
        pt.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"
        #路径变量
        self.img_path = tk.StringVar()
        #布局
        self.frame = tk.Frame(self)
        self.frame.pack(padx=10, pady=10)
        #标签
        self.lbl_file = tk.Label(self.frame, text="图像")
        self.lbl_file.grid(row=0, column=0)
        #输入框布局
        self.txt_file = tk.Entry(self.frame, width=60, textvariable=self.img_path)
        self.txt_file.grid(row=0, column=1, sticky=tk.W)
        #button形式以及布局
        self.btn_file = tk.Button(self.frame, text="选择", command=self.sel_img_file)
        self.btn_file.grid(row=0, column=1, sticky=tk.E)
        #同上
        self.lbl_txt = tk.Label(self.frame, text="文本")
        self.lbl_txt.grid(row=1, column=0)        
        self.txt_exract = tk.Text(self.frame)
        self.txt_exract.grid(row=1, column=1)        
        self.btn_extract = tk.Button(self.frame, text="提取文本", command=self.extract_text)
        self.btn_extract.grid(row=2, column=1, sticky=tk.W+tk.E)        
        
    def sel_img_file(self):
        self.img_path.set(filedialog.askopenfilename(title="选择图片", initialdir="."))

    def extract_text(self):
        if self.img_path:
            img = Image.open(self.img_path.get())
            text = pt.image_to_string(img, lang="chi_sim")
            self.txt_exract.delete(1.0, tk.END)
            self.txt_exract.insert(tk.END, text)

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    app = Application()
    app.mainloop()

    end_time = time.time()
    logger.info('process spend {} s.'.format(round(end_time - start_time, 3)))
    


