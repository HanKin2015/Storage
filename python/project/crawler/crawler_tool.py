# -*- coding: utf-8 -*-
"""
Created on Tue Nov 24 20:19:10 2020

@author: hankin
@description:
    Download picture crawler by python and tkinter
"""

import win32api
import win32con
from tkinter import filedialog, messagebox
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button 
import tkinter
import tkinter.font
import os, sys
import base64
import logging

# 导入可视化窗口库
current_working_dir_path = os.getcwd()
sys.path.append(current_working_dir_path)
#from visualized_window import VisualizedWindow
from libary import visualized_window

# ===== 全局变量 ====
local_dir_path = 'D:/Picture/'
if not os.path.exists(local_dir_path):
    os.makedirs(local_dir_path)

url = ''

# ===== 全局变量 =====

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename='./copy_tool.log',
                    filemode='a')



class CrawlerTool(VisualizedWindow):
    '''继承可视化窗口
    '''

    def __init__(self):
        '''初始化创建自己的类
        '''
        super().__init__()      # 在继承Tk这个类的基础上在自己的类中添加内容
        self.title("爬虫工具箱")
        

if __name__ == "__main__":
    app = CrawlerTool()
    app.mainloop()              # 程序运行




















