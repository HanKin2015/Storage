# -*- coding: utf-8 -*-
"""
Created on Tue Nov  11 19:36:49 2020

@author: hankin
@description:
    Visualized window template
"""
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

####### 全局变量 #######
working_dir_path = 'D:/visualized_window'
log_file_path = '{}/system.log'.format(working_dir_path)
logo_file_path = '{}/logo.ico'.format(working_dir_path)

window_title = 'Visualized Window'
window_width = 980
window_hight = 600

####### 全局变量 #######


if not os.path.exists(working_dir_path):
    os.makedirs(working_dir_path)

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                    datefmt='%a, %d %b %Y %H:%M:%S',
                    filename=log_file_path,
                    filemode='a')

class VisualizedWindow(tkinter.Tk):
    '''可视化窗口ui类
    '''
    
    def __init__(self):
        '''初始化自己的创建的CopyTool类
        '''
        super().__init__()      # 在继承Tk这个类的基础上在自己的类中添加内容
        self._generate_icon_()  # 生成图标ico文件，由于图片不能打包进exe文件中
        self._set_window_()     # 设置程序运行主窗口
        self._create_menu_bar_()# 创建菜单组件
        self._create_body_()    # 创建主体

    def _generate_icon_(self):
        '''将二进制图标转换为图片文件
        '''
        tmp = open(logo_file_path, "wb+")
        tmp.write(base64.b64decode(icon_img))
        tmp.close()

    def _set_window_(self):
        '''设置初始化窗口的属性
        '''
        self.title(window_title)    # 窗口名称
        self.resizable(False, False)# 不能伸缩
        #self.update()
        scn_width, scn_height = self.maxsize()  # 获得程序运行机器的分辨率（屏幕的长和宽）
        wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, (scn_width - window_width) //
                                        2, (scn_height - window_hight) // 2)
        self.geometry(wm_val)       # 将窗口设置在屏幕的中间
        self.iconbitmap(logo_file_path)  # 加载一下窗口的左上方显示的图片
        os.remove(logo_file_path)
        self.protocol('WM_DELETE_WINDOW', self.exit_window)  # 设置窗口关闭提醒

    def _create_menu_bar_(self):
        '''创建菜单栏
        '''
        menu_bar = tkinter.Menu(self)  # 继承原来Tk的Menu的对象

        # 文件菜单
        self.file_menu = tkinter.Menu(menu_bar, tearoff=0)
        self.file_menu.add_command(label='新建', accelerator='Ctrl+N', command=self.exit_window)
        self.file_menu.add_command(label='打开', accelerator='Ctrl+O', command=self.open_file)
        self.file_menu.add_command(label='保存', accelerator='Ctrl+S', command=self.save)
        self.file_menu.add_command(label='另存为', accelerator='Ctrl+Shift+S', command=self.save_as)
        self.file_menu.add_separator()  # 设置分割线
        self.file_menu.add_command(label='创建备份', accelerator='Alt+B', command=self.exit_window)
        self.file_menu.add_command(label='退出', accelerator='Alt+F4', command=self.exit_window)
        menu_bar.add_cascade(label='文件', menu=self.file_menu)  # 创建文件的菜单栏

        # 编辑菜单
        edit_menu = tkinter.Menu(menu_bar, tearoff=0)  # 基于菜单栏实例化“编辑”关联选项栏对象
        edit_menu.add_command(label='增加', accelerator='Ctrl+A', command=self.save)
        edit_menu.add_command(label='删除', accelerator='Ctrl+A', command=self.save)
        edit_menu.add_command(label='修改', accelerator='Ctrl+A', command=self.save)
        edit_menu.add_command(label='查询', accelerator='Ctrl+A', command=self.save)
        menu_bar.add_cascade(label='操作', menu=edit_menu)
 
        # 关于菜单
        about_menu = tkinter.Menu(menu_bar, tearoff=0)
        # 一般是全局的快捷键，比如帮助的快捷键一般是F1
        about_menu.add_command(label='帮助', command=lambda: self.show_messagebox('帮助'))
        # 注意需要把帮助文档绑定为全局事件
        self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox("帮助"))
        about_menu.add_command(label='更新日志', command=lambda: self.show_messagebox('更新日志'))  # 这里暂时未设置快捷键
        about_menu.add_command(label='关于', command=lambda: self.show_messagebox('关于'))
        menu_bar.add_cascade(label='关于', menu=about_menu)
        
        self['menu'] = menu_bar

    def show_messagebox(self, type):
        '''消息提示框
        '''
        if type == '帮助':
            messagebox.showinfo("帮助", "这是帮助文档！\nby hankin", icon='question')
        elif type == '更新日志':
            self.update_log_path = './update_log.log'
            try:
                update_log = open(self.update_log_path, 'r', encoding='utf-8').read()
            except Exception as ex:
                print('读取更新日志文件失败, error=', ex)
            messagebox.showinfo("更新日志", update_log, icon='question')
        elif type == '关于':
            messagebox.showinfo("关于", "CopyTool_V1.0.1.0")

    def _create_body_(self):
        '''主体部分
        '''
        # 设置字体slant=tf.ITALIC,underline=1,overstrike=1,consolas
        ft = tkinter.font.Font(
            family=r'微软雅黑', weight=tkinter.font.NORMAL, size=12)

        # 上面部分
        fm_up = tkinter.Frame(self)
        # fm_up.propagate(0)
        self.input_content = tkinter.Entry(fm_up, width=30, font=ft)
        self.input_content.pack(
            side=tkinter.LEFT, expand=True, fill=tkinter.X, padx=5, pady=5)

        # self.input_content.bind(sequence="<Button-1><ButtonRelease-1>", func=mourse_double_clicked)  #单击鼠标左键
        self.input_content.bind(
            sequence="<Double-Button-1><ButtonRelease-1>", func=self.mourse_double_clicked)  # 双击鼠标左键

        upload_btn = tkinter.Button(fm_up, text='send', width=10, height=1,
                                    command=lambda: self.upload_btn_cliecked(self.content_text), font=ft, compound='center')
        upload_btn.pack(side=tkinter.LEFT, pady=5)
        download_btn = tkinter.Button(fm_up, text='recive', width=10, height=1,
                                      command=lambda: self.download_btn_cliecked(self.content_text), font=ft, compound='center')
        download_btn.pack(side=tkinter.LEFT, padx=5)

        fm_up.pack(fill=tkinter.X)

        # 中间部分
        fm_mid = tkinter.Frame(self)
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

        # 下面部分：拷贝按钮
        fm_down = tkinter.Frame(self)
        # fm_down.propagate(0)
        copy_btn = tkinter.Button(fm_down, text='copy', command=lambda: self.copy_btn_cliecked(
            self.content_text), font=ft, compound='center')
        copy_btn.pack(fill='both')
        fm_down.pack(fill='x')

    def exit_window(self):
        '''退出窗口提示框
        '''
        if messagebox.askokcancel('退出?', '确定退出吗?'):  # 设置文本提示框
            self.destroy()  # 满足条件的话主窗口退出

    def open_file(self, event=None):
        '''打开文件框
        '''
        input_file = filedialog.askopenfilename(
            filetypes=[('所有文件', '*.*'), ('文本文档', '*.txt')])  # 弹出文件对话框，设置选择文件的类型
        if input_file:
            print(input_file)

    def save(self, event=None):
        if not self.file_name:  # 这里就体现出来之前设置的self.file_name全局变量的作用了
            self.save_as()  # 没有有文件名称的另保存
        else:
            self._write_to_file(self.file_name)  # 有文件名称的直接写入文件（保存本地）

    def save_as(self, event=None):
        input_file = filedialog.asksaveasfilename(  # 注意这里弹出的是文件保存对话框
            filetypes=[('所有文件', '*.*'), ('文本文档', '*.txt')]
        )
        if input_file:  # 还是要对用户操作进行判定
            self.file_name = input_file  # 设置文件名称
            self._write_to_file(self.file_name)  # 写入本地

    def mourse_double_clicked(self, event):
        logging.info('mouse position is x={}, y={}'.format(event.x, event.y))
        input_file = filedialog.askopenfilename(  # 注意这里弹出的是文件保存对话框
            filetypes=[('所有文件', '*.*'), ('文本文档', '*.txt')]
        )
        if input_file:
            # 先清除内容
            self.input_content.delete(0, 'end')
            self.input_content.insert(0, input_file)

    def write_to_file(self, file_name):
        try:
            content = self.content_text.get(1.0, 'end')  # 先获取文本框中的所有数据
            with open(file_name, 'w') as the_file:
                the_file.write(content)  # 将数据写入到本地的文件中
            # 这一步就是显示当前窗口的标题不变，可以尝试注释一下这行代码
            self.title("%s - EditorPlus" % os.path.basename(file_name))
        except IOError:
            messagebox.showwarning("保存", "保存失败！")  # 如果保存失败的话，会弹出消息对话框

if __name__ == "__main__":
    app = VisualizedWindow()
    app.mainloop()              # 程序运行










