# -*- coding: utf-8 -*-
"""
Created on Fri Sep 11 19:59:08 2020

@author: Administrator
"""

import win32api
import win32con
from tkinter import filedialog, messagebox  # 这两个需要单独导入
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button  # 导入ttk模块中的指定几个组件
import tkinter
import tkinter.font
import os
import ftplib
import base64
import logging

class CopyTool(tkinter.Tk):
    '''主窗口ui类
    '''

    def __init__(self):
        '''初始化自己的创建的CopyTool类
        '''

        super().__init__()  # 在继承Tk这个类的基础上在自己的类中添加内容
        self._set_window_()  # 设置程序运行主窗口
        self._create_menu_bar_()  # 创建菜单组件

    def _set_window_(self):
        '''设置初始化窗口的属性
        '''

        self.title("CopyTool")  # 窗口名称
        self.resizable(False, False)
        # self.update()
        scn_width, scn_height = self.maxsize()  # 获得程序运行机器的分辨率（屏幕的长和宽）
        wm_val = '750x450+{}+{}'.format((scn_width - 750) //
                                        2, (scn_height - 450) // 2)
        self.geometry(wm_val)  # 将窗口设置在屏幕的中间
        self.iconbitmap("copy_tool.ico")  # 加载一下窗口的左上方显示的图片
        os.remove("copy_tool.ico")
        self.protocol('WM_DELETE_WINDOW', self.exit_copy_tool)  # 设置窗口关闭提醒

    def _create_menu_bar_(self):
        '''创建菜单栏
        '''
        menu_bar = tkinter.Menu(self)  # 继承原来Tk的Menu的对象

        file_menu = tkinter.Menu(menu_bar, tearoff=0)
        file_menu.add_command(
            label='新建', accelerator='Ctrl+N', command=self.new_file)
        file_menu.add_command(
            label='打开', accelerator='Ctrl+O', command=self.open_file)
        file_menu.add_command(
            label='保存', accelerator='Ctrl+S', command=self.save)
        file_menu.add_command(
            label='另存为', accelerator='Ctrl+Shift+S', command=self.save_as)
        file_menu.add_separator()  # 设置分割线
        file_menu.add_command(
            label='退出', accelerator='Alt+F4', command=self.exit_copy_tool)
        menu_bar.add_cascade(label='文件', menu=file_menu)  # 创建文件的菜单栏

        # FTP菜单
        ftp_menu = tkinter.Menu(menu_bar, tearoff=0)
        ftp_menu.add_separator()  # 设置分割线
        ftp_menu.add_command(
            label='上传', accelerator='Ctrl+U', command=self.upload_file)
        ftp_menu.add_command(
            label='下载', accelerator='Ctrl+D', command=self.down_file)
        ftp_menu.add_separator()  # 设置分割线
        ftp_menu.add_command(label='清理', accelerator='Ctrl+L',
                             command=self.clear_remote_dir)
        ftp_menu.add_separator()  # 设置分割线
        ftp_menu.add_command(
            label='发送指定文件', accelerator='Ctrl+Q', command=self.send_assign_file)
        ftp_menu.add_command(
            label='接收指定文件', accelerator='Ctrl+W', command=self.recv_assign_file)
        menu_bar.add_cascade(label='FTP', menu=ftp_menu)

        # 编辑菜单
        edit_menu = tkinter.Menu(menu_bar, tearoff=0)  # 基于菜单栏实例化“编辑”关联选项栏对象
        edit_menu.add_command(label='撤销', accelerator='Ctrl+Z',
                              command=lambda: self.handle_menu_action('撤销'))
        edit_menu.add_command(label='恢复', accelerator='Ctrl+Y',
                              command=lambda: self.handle_menu_action('恢复'))
        edit_menu.add_separator()
        edit_menu.add_command(label='剪切', accelerator='Ctrl+X',
                              command=lambda: self.handle_menu_action('剪切'))
        edit_menu.add_command(label='复制', accelerator='Ctrl+C',
                              command=lambda: self.handle_menu_action('复制'))
        edit_menu.add_command(label='粘贴', accelerator='Ctrl+V',
                              command=lambda: self.handle_menu_action('粘贴'))
        edit_menu.add_separator()
        edit_menu.add_command(label='全选', accelerator='Ctrl+A',
                              command=lambda: self.handle_menu_action('全选'))
        # 将“编辑”关联选项栏放在“编辑”菜单栏上
        menu_bar.add_cascade(label='编辑', menu=edit_menu)

        # 视图菜单
        view_menu = tkinter.Menu(menu_bar, tearoff=0)  # 将“视图”关联选项栏放在“视图”菜单栏上
        # 为了方便定义的这个变量在类中其他的函数中使用，这里将变量变成类中的实例属性
        self.is_show_line_num = tkinter.IntVar()
        self.is_show_line_num.set(1)
        view_menu.add_checkbutton(label='显示行号', variable=self.is_show_line_num,
                                  command=self._update_line_num_)
        self.is_highlight_line = tkinter.IntVar()  # 这里也是和上面一样，因为后面要用到这个变量
        view_menu.add_checkbutton(label='高亮当前行', onvalue=1, offvalue=0,
                                  variable=self.is_highlight_line, command=self._toggle_highlight)  # 通过checkbutton来实现功能

        # 在主题菜单中再添加一个子菜单
        theme_menu = tkinter.Menu(menu_bar, tearoff=0)
        self.theme_choice = tkinter.StringVar()
        self.theme_choice.set('Default')
        for k in sorted(theme_color):  # 这里的theme_color就是之前从editor_style.py文件中导入的参数内容
            theme_menu.add_radiobutton(
                label=k, variable=self.theme_choice, command=self.change_theme)
        view_menu.add_cascade(label='主题', menu=theme_menu)  # 注意这里添加的菜单栏指定的对象
        menu_bar.add_cascade(label='视图', menu=view_menu)  # 注意这里添加的菜单栏指定的对象

        # 关于菜单
        about_menu = tkinter.Menu(menu_bar, tearoff=0)
        about_menu.add_command(
            label='关于', command=lambda: self.show_messagebox('关于'))  # 这里暂时未设置快捷键
        # 一般是全局的快捷键，比如帮助的快捷键一般是F1
        about_menu.add_command(
            label='帮助', command=lambda: self.show_messagebox('帮助'))
        menu_bar.add_cascade(label='关于', menu=about_menu)
        # 注意需要把帮助文档绑定为全局事件
        self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox("帮助"))

        self['menu'] = menu_bar

    def show_messagebox(self, type):
        if type == "帮助":
            messagebox.showinfo("帮助", "这是帮助文档！\nby hankin", icon='question')
        else:
            messagebox.showinfo("关于", "CopyTool_V4.2")      
            
 
if __name__ == "__main__":
    app = CopyTool()  # 类的实例化
    app.mainloop()  # 程序运行           
            
            
            
            
            
            