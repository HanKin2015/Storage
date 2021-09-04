# -*- coding: utf-8 -*-
"""
文 件 名: study_component_style.py
文件描述: 学习tkinter组件风格
作    者: HanKin
创建日期: 2021.08.30
修改日期：2021.08.30

Copyright (c) 2021 HanKin. All rights reserved.
"""

import tkinter
import base64
from icon import icon_img   # 图标二进制文件
import os
# 必须这种形式from tkinter import *不行 import tkMessageBox不行
# 可以是from tkinter import messagebox
import tkinter.messagebox
import tkinter.font
from tkinter.ttk import Scrollbar

# 工作目录
work_path = './'

# logo图标生成保存路径(由py文件生成)
logo_path = '{}/logo.ico'.format(work_path)

# 窗口标题
window_title = '学习tkinter组件风格'

# 窗口宽度
window_width = 980

# 窗口高度
window_hight = 600

class study_component_style(tkinter.Tk):
    '''tkinter学习组件风格类
    '''
    
    def __init__(self):
        '''初始化函数
        '''
    
        super().__init__()      # 在继承Tk这个类的基础上在自己的类中添加内容
        self._generate_icon_()  # 生成图标ico文件，由于图片不能打包进exe文件中
        self._set_window_()     # 设置程序运行主窗口
        self._create_menu_bar_()# 创建菜单组件
        self._create_body_()    # 创建主体

    def _generate_icon_(self):
        '''将二进制图标转换为图片文件(需要先转换成py文件)
        '''
        
        tmp = open(logo_path, "wb+")
        tmp.write(base64.b64decode(icon_img))
        tmp.close()

    def _set_window_(self):
        '''设置初始化窗口的属性
        '''
        
        self.title(window_title)                # 窗口名称
        self.resizable(False, False)            # 不能伸缩
        #self.update()
        scn_width, scn_height = self.maxsize()  # 获得程序运行机器的分辨率（屏幕的长和宽）
        wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, (scn_width - window_width) //
                                        2, (scn_height - window_hight) // 2)
        self.geometry(wm_val)       # 将窗口设置在屏幕的中间
        self.iconbitmap(logo_path)  # 加载一下窗口的左上方显示的图片
        os.remove(logo_path)
        self.protocol('WM_DELETE_WINDOW', self.exit_window)  # 设置窗口关闭提醒
        
        #self.geometry('300x300+500+100')   # 设置宽度300,高度300,距离左上角x轴距离为500,y轴距离为100
        self.attributes('-alpha', '0.9')    # 设置透明度,数值是0-1之间的小数,包含0和1
        #self.iconbitmap('ico.ico')         # 添加图标
        #self.title('标题')                 # 添加标题
        self.config()                       # 设置背景颜色
        self.attributes("-fullscreen", False)   # 设置全屏
        self.attributes("-topmost", False)      # 设置窗体置于最顶层
        self.update()                       # 刷新窗口,否则获取的宽度和高度不准
        width = self.winfo_width()          # 获取窗口宽度
        print(f'width:{width}')
        height = self.winfo_height()        # 获取窗口高度
        print(f'height:{height}')
        self.overrideredirect(False)        # 去除窗口边框

        width = self.winfo_screenwidth()    # 获取屏幕宽度
        print(f'screen width:{width}')
        height = self.winfo_screenheight()  # 获取屏幕高度
        print(f'screen height:{height}')

        x = self.winfo_x()  # 获取距离屏幕左上角的x轴距离,即x轴的坐标
        print(f'x:{x}')
        y = self.winfo_y()  # 获取距离屏幕左上角的y轴距离,即y轴的坐标
        print(f'y:{y}')

    def _create_menu_bar_(self):
        '''创建菜单栏
        '''
        menu_bar = tkinter.Menu(self)  # 继承原来Tk的Menu的对象

        # 文件菜单
        self.file_menu = tkinter.Menu(menu_bar, tearoff=0)
        self.file_menu.add_command(label='创建子窗口', accelerator='Ctrl+N', command=self.set_ftp)
        self.file_menu.add_separator()  # 设置分割线
        self.file_menu.add_command(label='退出', accelerator='Alt+F4', command=self.exit_window)
        menu_bar.add_cascade(label='文件', menu=self.file_menu)  # 创建文件的菜单栏
        
        self['menu'] = menu_bar

    def set_ftp(self):
        '''创建子窗口相对于父窗口居中对齐
        '''
        
        set_ftp_window = tkinter.Toplevel(self)
        set_ftp_window.title('设置FTP服务器')
        window_width = 200
        window_hight = 100
        pos_x = self.winfo_rootx() + ((self.winfo_width() - window_width) // 2)
        pos_y = self.winfo_rooty() - 20 + ((self.winfo_height() - window_hight) // 2)
        wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, pos_x, pos_y)
        set_ftp_window.geometry(wm_val)       # 将窗口设置在屏幕的中间
        
        ip_label = tkinter.Label(set_ftp_window, text='ip地址：', justify=tkinter.LEFT)
        ip_entry = tkinter.Entry(set_ftp_window, text='')
        user_label = tkinter.Label(set_ftp_window, text='用户名：', justify=tkinter.LEFT)
        user_entry = tkinter.Entry(set_ftp_window, text='')
        pwd_label = tkinter.Label(set_ftp_window, text='密   码：', justify=tkinter.LEFT)
        pwd_entry = tkinter.Entry(set_ftp_window, text='')
        ip_label.grid(row=0, column=0)
        ip_entry.grid(row=0, column=1)
        user_label.grid(row=1, column=0)
        user_entry.grid(row=1, column=1)
        pwd_label.grid(row=2, column=0, sticky=tkinter.W)
        pwd_entry.grid(row=2, column=1, sticky=tkinter.W)
        
        qry_btn = tkinter.Button(set_ftp_window, text='确定', width=10, height=1,
                                      command=lambda: self.qry_btn_clicked(), compound='right')
        qry_btn.grid(row=3, column=1, sticky=tkinter.E)
        
        set_ftp_window.mainloop()
    
    def exit_window(self):
        '''退出窗口提示框
        '''
        if tkinter.messagebox.askokcancel('退出?', '确定退出吗?'):  # 设置文本提示框
            self.destroy()  # 满足条件的话主窗口退出
            
    def _create_body_(self):
        '''主体部分
        '''
        # 设置字体slant=tf.ITALIC,underline=1,overstrike=1,consolas
        ft = tkinter.font.Font(
            family=r'微软雅黑', weight=tkinter.font.NORMAL, size=12)

        # 上面部分
        fm_up = tkinter.Frame(self)
        # fm_up.propagate(0)
        label1 = tkinter.Label(fm_up, text='俺是一个标准：', justify=tkinter.LEFT)
        entry1 = tkinter.Entry(fm_up, text='')
        label1.grid(row=1, column=0)
        entry1.grid(row=1, column=1)
        
        label2 = tkinter.Label(fm_up, text='左对齐：', justify=tkinter.LEFT)
        entry2 = tkinter.Entry(fm_up, text='')
        label2.grid(row=2, column=0, sticky=tkinter.W)
        entry2.grid(row=2, column=1, sticky=tkinter.W)
        
        label3 = tkinter.Label(fm_up, text='默认对齐：')
        entry3 = tkinter.Entry(fm_up, text='')
        label3.grid(row=3, column=0)
        entry3.grid(row=3, column=1)
        
        btn1 = tkinter.Button(fm_up, text='右对齐', width=10, height=1,
                                      command=lambda: self.qry_btn_clicked())
        btn1.grid(row=4, column=1, sticky=tkinter.E)
        btn2 = tkinter.Button(fm_up, text='默认对齐', width=10, height=1,
                                      command=lambda: self.qry_btn_clicked())
        btn2.grid(row=5, column=1)

        fm_up.pack(fill=tkinter.X)

        # 中间部分
        fm_mid = tkinter.Frame(self)
        fm_mid.propagate(0)

        # 创建文本输入框
        self.content_text = tkinter.Text(
            fm_mid, wrap='word', undo=True, font=ft)
        self.content_text.pack(expand='yes', fill='both')
        self.content_text.bind('<Control-C>', self.copy_btn_cliecked(self.content_text))
        self.content_text.bind('<Control-c>', self.copy_btn_cliecked(self.content_text))
        self.content_text.bind('<Alt-F4>', self.exit_window)
        self.content_text.tag_configure('active_line', background='#EEEEE0')
        self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox("帮助"))

        # 创建滚动条
        scroll_bar = Scrollbar(self.content_text)
        scroll_bar['command'] = self.content_text.yview
        self.content_text['yscrollcommand'] = scroll_bar.set
        scroll_bar.pack(side='right', fill='y')

        fm_mid.pack(fill=tkinter.BOTH, expand='yes')

        # 下面部分：拷贝按钮
        fm_down = tkinter.Frame(self)
        # fm_down.propagate(0)
        copy_btn = tkinter.Button(fm_down, text='copy', command=lambda: self.copy_btn_cliecked(
            self.content_text), font=ft, compound='center')
        copy_btn.pack(fill='both')
        fm_down.pack(fill='x')
    
    def qry_btn_clicked(self):
        print("hello world")
    
    def copy_btn_cliecked(self, display_content):
        '''
        复制内容按钮点击事件
        '''
        # 打印显示内容
        content = display_content.get('0.0', 'end').strip()

        # 将内容弄到剪切板
        display_content.event_generate('<<SelectAll>>')
        display_content.event_generate('<<Copy>>')

if __name__ == "__main__":
    app = study_component_style()
    app.mainloop()              # 程序运行