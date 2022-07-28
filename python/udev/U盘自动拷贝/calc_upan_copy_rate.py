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
import tkinter.filedialog
import tkinter.font
import time
import shutil
import psutil
import logging
import shutil

# 工作目录
work_path = './'

# U盘内容拷贝到指定路径,不存在会自动创建
upan_file_to_local_path = 'D:/usb/content/'

# 本地文件到U盘位置
local_file_to_upan = ''

# 窗口标题
window_title = '计算U盘拷贝速度'

# 窗口宽度
window_width = 480

# 窗口高度
window_hight = 320

class calc_upan_copy_rate_gui(tkinter.Tk):
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

        self.columnconfigure(1, weight=1)

        tkinter.Label(self, text='本地文件地址：', justify=tkinter.LEFT).grid(row=0, column=0)
        local_path = tkinter.Entry(self, text='', highlightcolor='red', highlightthickness=1)
        local_path.grid(row=0, column=1, columnspan=2, sticky=tkinter.E+tkinter.N+tkinter.W+tkinter.S)
        local_path.bind(sequence='<Double-Button-1><ButtonRelease-1>', func=lambda arg: self.mourse_double_clicked(arg, local_path))  # 双击鼠标左键
        tkinter.Button(self, text='拷贝到U盘', command=lambda: self.copy_btn_clicked(local_path), compound='right').grid(row=0, column=3, sticky=tkinter.E)

        tkinter.Label(self, text='U盘文件地址：', justify=tkinter.LEFT).grid(row=1, column=0)
        upan_path = tkinter.Entry(self, text='', highlightcolor='red', highlightthickness=1)
        upan_path.grid(row=1, column=1, columnspan=2, sticky='nesw')
        upan_path.bind(sequence='<Double-Button-1><ButtonRelease-1>', func=lambda arg: self.mourse_double_clicked(arg, upan_path))  # 双击鼠标左键
        tkinter.Button(self, text='拷贝到本地', command=lambda: self.copy_btn_clicked(upan_path), compound='right').grid(row=1, column=3, sticky=tkinter.E)

        tkinter.Label(self, text='拷贝时间：', justify=tkinter.LEFT).grid(row=2, column=0, sticky=tkinter.W)
        self.cpoy_time_value = tkinter.StringVar()
        self.cpoy_time_value.set('0秒')
        tkinter.Label(self, textvariable=self.cpoy_time_value).grid(row=2, column=1)
        tkinter.Button(self, text='检测是否存在U盘', command=lambda: self.check_btn_clicked(), compound='right').grid(row=2, column=2, sticky=tkinter.E)
        
        tkinter.Label(self, text='拷贝速度：', justify=tkinter.LEFT).grid(row=3, column=0, sticky=tkinter.W)
        copy_rate = tkinter.Label(self, text='0 MB/s', justify=tkinter.RIGHT).grid(row=3, column=1)

        tkinter.Label(self, text='', justify=tkinter.LEFT).grid(row=4, column=0, sticky=tkinter.W)
        tkinter.Label(self, text='文件信息', justify=tkinter.LEFT).grid(row=5, column=0, sticky=tkinter.W)
        tkinter.Label(self, text='文件名：', justify=tkinter.LEFT).grid(row=6, column=0, sticky=tkinter.W)
        self.file_name = tkinter.StringVar()
        tkinter.Label(self, textvariable=self.file_name, justify=tkinter.LEFT).grid(row=6, column=1, sticky=tkinter.W)
        tkinter.Label(self, text='文件大小：', justify=tkinter.LEFT).grid(row=7, column=0, sticky=tkinter.W)
        self.file_size = tkinter.StringVar()
        tkinter.Label(self, textvariable=self.file_size, justify=tkinter.LEFT).grid(row=7, column=1, sticky=tkinter.W)
        tkinter.Label(self, text='拷贝时间：', justify=tkinter.LEFT).grid(row=8, column=0, sticky=tkinter.W)
        self.copy_time = tkinter.StringVar()
        tkinter.Label(self, textvariable=self.copy_time, justify=tkinter.LEFT).grid(row=8, column=1, sticky=tkinter.W)

    def mourse_double_clicked(self, event, entry):
        print('mouse position is x={}, y={}'.format(event.x, event.y))
        input_file = tkinter.filedialog.askopenfilename(  # 注意这里弹出的是文件保存对话框
            filetypes=[('所有文件', '*.*'), ('文本文档', '*.txt')]
        )
        if input_file:
            # 先清除内容
            entry.delete(0, 'end')
            entry.insert(0, input_file)

    def check_btn_clicked(self):
        '''检测是否存在大容量存储设备
        '''
        
        is_exist = False
        
        # 检测所有的驱动器，进行遍历寻找哦
        for item in psutil.disk_partitions():
            print('device: {}, opts: {}'.format(item.device, item.opts))
            if 'removable' in item.opts:
                driver, opts = item.device, item.opts
                # 输出可移动驱动器符号
                print('发现usb驱动:'.format(driver))
                tkinter.messagebox.showinfo('检查结果', '发现存储设备驱动器符号:'.format(driver))
                is_exist = True
                break
            # 没有找到可输出驱动器
            else:
                print('没有找到可移动驱动器')
                continue
        
        if not is_exist:
            tkinter.messagebox.showwarning('检查结果', '当前无大容量存储设备')

    def copy_btn_clicked(self, entry):
        '''
        '''

        copy_time = 0
        while copy_time < 5:
            time.sleep(1)
            copy_time += 1
            self.cpoy_time_value.set('{} 秒'.format(copy_time))
            self.update()

        path = entry.get().strip()
        print(path)
        file_name = path[path.rfind('/')+1:]
        file_size = round(os.path.getsize(path) / 1024 / 1024, 1)
        copy_time = 123
        self.file_name.set(file_name)
        self.file_size.set('{} MB'.format(file_size))
        self.copy_time.set('{} s'.format(copy_time))

if __name__ == "__main__":
    app = calc_upan_copy_rate_gui()
    app.mainloop()