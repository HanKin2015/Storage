# -*- coding: utf-8 -*-
"""
文 件 名: study_component_style.py
文件描述: 检测U盘的插入，以及进行自动复制文件并写入文件
作    者: HanKin
创建日期: 2021.08.30
修改日期：2021.08.30

Copyright (c) 2021 HanKin. All rights reserved.
"""

import tkinter
import base64
from icon import icon_img   # 图标二进制文件
import os
from tkinter import *

# 工作目录
work_path = './'

# logo图标生成保存路径(由py文件生成)
logo_path = '{}/logo.ico'.format(work_path)

# 窗口标题
window_title = '学习tkinter组件'

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
        #self._create_menu_bar_()# 创建菜单组件
        #self._create_body_()    # 创建主体

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
    
    def exit_window(self):
        '''退出窗口提示框
        '''
        if tkinter.messagebox.askokcancel('退出?', '确定退出吗?'):  # 设置文本提示框
            self.destroy()  # 满足条件的话主窗口退出

if __name__ == "__main__":
    app = study_component_style()
    app.mainloop()              # 程序运行