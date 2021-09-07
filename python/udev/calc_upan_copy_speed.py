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
import os
import tkinter.messagebox
import tkinter.font

# 工作目录
work_path = './'

# 窗口标题
window_title = '计算U盘拷贝速度'

# 窗口宽度
window_width = 980

# 窗口高度
window_hight = 600

class calc_upan_copy_speed_gui(tkinter.Tk):
    '''gui类
    '''
    
    def __init__(self):
        '''初始化函数
        '''
    
        super().__init__()      # 在继承Tk这个类的基础上在自己的类中添加内容
        self._set_window_()     # 设置程序运行主窗口
        self._create_body_()    # 创建主体

    def _set_window_(self):
        '''设置初始化窗口的属性
        '''
        
        self.title(window_title)                # 窗口名称
        self.resizable(False, False)            # 不能伸缩
        scn_width, scn_height = self.maxsize()  # 获得程序运行机器的分辨率（屏幕的长和宽）
        wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, (scn_width - window_width) //
                                        2, (scn_height - window_hight) // 2)
        self.geometry(wm_val)       # 将窗口设置在屏幕的中间
        self.protocol('WM_DELETE_WINDOW', self.exit_window)  # 设置窗口关闭提醒

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
            
        ip_label = tkinter.Label(self, text='ip地址：', justify=tkinter.LEFT)
        ip_entry = tkinter.Entry(self, text='')
        user_label = tkinter.Label(self, text='用户名：', justify=tkinter.LEFT)
        user_entry = tkinter.Entry(self, text='')
        pwd_label = tkinter.Label(self, text='密   码：', justify=tkinter.LEFT)
        pwd_entry = tkinter.Entry(self, text='')
        ip_label.grid(row=0, column=0)
        ip_entry.grid(row=0, column=1)
        user_label.grid(row=1, column=0)
        user_entry.grid(row=1, column=1)
        pwd_label.grid(row=2, column=0, sticky=tkinter.W)
        pwd_entry.grid(row=2, column=1, sticky=tkinter.W)
        
        qry_btn = tkinter.Button(self, text='确定', width=10, height=1,
                                      command=lambda: self.qry_btn_clicked(), compound='right')
        qry_btn.grid(row=3, column=1, sticky=tkinter.E)
    

if __name__ == "__main__":
    app = calc_upan_copy_speed_gui()
    app.mainloop()