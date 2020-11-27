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

# 增加libary库的搜索路径
sys.path.append('../../libary/')

# 导入可视化窗口库
from visualized_window import VisualizedWindow
# 导入自定义的Entry库
from entrywithplaceholder import EntryWithPlaceholder

# 全局变量
local_dir_path = 'D:/Picture/'
if not os.path.exists(local_dir_path):
    os.makedirs(local_dir_path)

url = ''
log_file_path = './crawler_tool.log'

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename=log_file_path,
                    filemode='a')



class CrawlerTool(VisualizedWindow):
    '''继承可视化窗口
    '''

    def __init__(self):
        '''初始化创建自己的类
        '''
        super().__init__()      # 在继承Tk这个类的基础上在自己的类中添加内容
        self.title("爬虫工具箱")
    
    def _create_body_(self):
        '''重写主体布局
        绝对布局：label.place(x=10, y=10)
        相对布局：label.pack(fill=tkinter.X, side=tkinter.TOP)
        表格布局：label.grid(row=0, column=0)
        tkinter.LEFT
        tkinter.BOTTOM
        tkinter.TOP
        tkinter.RIGHT
        
        entry无placeholder
        '''
        # 设置字体slant=tf.ITALIC,underline=1,overstrike=1,consolas
        ft = tkinter.font.Font(family=r'微软雅黑', weight=tkinter.font.NORMAL, size=12)

        # 上面部分
        fm_up = tkinter.Frame()
        #self.input_content = tkinter.Entry(fm_up, width=30, font=ft)
        
        self.default_url = tkinter.ttk.Combobox(fm_up, textvariable=tkinter.StringVar(), font=ft)
        self.default_url['values'] = ('招商', '越秀', '中海')
        #self.default_url.current(0)
        self.default_url.grid(row=0, column=0)
        
        self.crawling_url = EntryWithPlaceholder(fm_up, '请输入爬取网址', font=ft)
        self.crawling_url.grid(row=0, column=1)
        self.crawling_regex = EntryWithPlaceholder(fm_up, '请输入爬取规则', font=ft)
        self.crawling_regex.grid(row=1, column=0, sticky=tkinter.E+tkinter.W)
        self.crawling_index = EntryWithPlaceholder(fm_up, '请输入爬取索引', font=ft)
        self.crawling_index.grid(row=1, column=1)

        crawling_btn = tkinter.Button(fm_up, text='爬取', width=10, height=1, font=ft,
                                    command=lambda: self.crawling_btn_cliecked(), compound='center')
        crawling_btn.grid(row=0, column=2)
        analysis_btn = tkinter.Button(fm_up, text='分析', width=10, height=1, font=ft,
                                      command=lambda: self.analysis_btn_cliecked(self.content_text),compound='center')
        analysis_btn.grid(row=1, column=2)

        fm_up.pack(fill=tkinter.X)

        # 中间部分
        fm_mid = tkinter.Frame()
        fm_mid.propagate(0)

        # 创建文本输入框
        self.content_text = tkinter.Text(
            fm_mid, wrap='word', undo=True, font=ft)
        self.content_text.pack(expand='yes', fill='both')
        self.content_text.bind('<Control-O>', self.open_file)
        self.content_text.bind('<Control-o>', self.open_file)
        self.content_text.bind('<Alt-F4>', self.exit_window)
        self.content_text.tag_configure('active_line', background='#EEEEE0')
        self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox("帮助"))

        # 创建滚动条
        scroll_bar = Scrollbar(self.content_text)
        scroll_bar['command'] = self.content_text.yview
        self.content_text['yscrollcommand'] = scroll_bar.set
        scroll_bar.pack(side='right', fill='y')

        fm_mid.pack(fill=tkinter.BOTH, expand='yes')

        # 下面部分：预留部分
        fm_down = tkinter.Frame()
        # fm_down.propagate(0)
        copy_btn = tkinter.Button(fm_down, text='青春的羽翼,划破伤痛的记忆', font=ft, compound='center')
        copy_btn.pack(fill='both')
        fm_down.pack(fill='x')
        
    def crawling_btn_cliecked(self):
        print(self.crawling_url.get())
        print(self.crawling_regex.get())
        print(self.crawling_index.get())
if __name__ == "__main__":
    app = CrawlerTool()
    app.mainloop()              # 程序运行




















