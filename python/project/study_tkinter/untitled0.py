# -*- coding: utf-8 -*-
"""
Created on Thu Sep  3 13:16:42 2020

@author: Administrator
"""

import io    
from PIL import Image, ImageTk    
import tkinter as tk    
  
#对一个pil_image对象进行缩放，让它在一个矩形框内，还能保持比例   
 
def resize( w_box, h_box, pil_image): #参数是：要适应的窗口宽、高、Image.open后的图片
  w, h = pil_image.size #获取图像的原始大小   
  f1 = 1.0*w_box/w 
  f2 = 1.0*h_box/h    
  factor = min([f1, f2])   
  width = int(w*factor)    
  height = int(h*factor)    
  return pil_image.resize((width, height), Image.ANTIALIAS)    
 
 
root = tk.Tk()    #创建窗口，必须在ImageTk.PhotoImage()之前！
 
#resize函数使用过程：  
#==================================================================
w_box = 700    #期望图像显示的大小（窗口大小）
h_box = 100    
 
pil_image = Image.open(r'img/copy.png')    #以一个PIL图像对象打开  【调整待转图片格式】  
 
pil_image_resized = pil_image.resize((18, 18), Image.ANTIALIAS)    #缩放图像让它保持比例，同时限制在一个矩形框范围内  【调用函数，返回整改后的图片】  
 
tk_image = ImageTk.PhotoImage(pil_image_resized)    # 把PIL图像对象转变为Tkinter的PhotoImage对象  【转换格式，方便在窗口展示】  
#====================================================================  
  
 
# Label: 这个小工具，就是个显示框，小窗口，把图像大小显示到指定的显示框     
label = tk.Label(root, image=tk_image, width=w_box, height=h_box)    
#padx,pady是图像与窗口边缘的距离     
label.pack(padx=5, pady=5)    
root.mainloop()    