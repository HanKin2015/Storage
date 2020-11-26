# -*- coding: utf-8 -*-
"""
Created on Tue Nov 26 19:36:49 2020

@author: hankin
@description:
    unit test in libary
"""

from visualized_window import VisualizedWindow
import win32api
import win32con
from tkinter import filedialog, messagebox  
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button 
import tkinter
import tkinter.font
import os
import logging
import base64
from icon import icon_img   # 图标二进制文件

class CrawlerTool(VisualizedWindow):
    def __init__(self):
        '''初始化自己的创建的CopyTool类
        '''
        super().__init__()      # 在继承Tk这个类的基础上在自己的类中添加内容
        self.title("窗口可视化")
        self.file_menu.add_command(label='保存7', accelerator='Ctrl+S', command=self.exit_window)
        
    def exit_window(self):
        '''退出窗口提示框
        '''
        if messagebox.askokcancel('退出123?', '确定退出吗?'):  # 设置文本提示框
            self.destroy()  # 满足条件的话主窗口退出

if __name__ == "__main__":
    app = CrawlerTool()
    app.mainloop()              # 程序运行