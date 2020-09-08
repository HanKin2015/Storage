# -*- coding: utf-8 -*-
"""
Created on Mon Sep  7 21:00:02 2020

@author: Administrator
"""

import tkinter as tk
import tkinter.font as tf
import win32api,win32con
from ftplib import FTP
from tkinter import filedialog, messagebox #这两个需要单独导入
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button #导入ttk模块中的指定几个组件
import tkinter
import PIL
from PIL import ImageTk

class CopyTool(tkinter.Tk):
	
	def __init__(self):     #初始化自己的创建的CopyTool类
		super().__init__()  #在继承Tk这个类的基础上在自己的类中添加内容
		self._set_window_() #设置程序运行主窗口


    
if __name__ == "__main__":
	app = CopyTool()      #类的实例化
	app.mainloop()			#程序运行
    
    