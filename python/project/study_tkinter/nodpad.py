# -*- coding: utf-8 -*-
"""
Created on Wed Sep  2 13:30:46 2020

@author: Administrator
"""

import os #系统模块
from editor_style import theme_color, ICONS #这里就是从之前命名的文件中导入两个参数
from tkinter import *  #导入tkinter中所有的方法
from tkinter import filedialog, messagebox #这两个需要单独导入
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button #导入ttk模块中的指定几个组件
import tkinter
import PIL 

#继承Tk这个类
class EditorPlus(tkinter.Tk):
	icon_res = []
	file_name = None
	
	def __init__(self):     #初始化自己的创建的EditorPlus类
		super().__init__()  #在继承Tk这个类的基础上在自己的类中添加内容
		self._set_window_() #设置程序运行主窗口
		self._create_menu_bar_()	#创建菜单组件
		self._create_shortcut_bar_()
		self._create_body_()
        
	def _create_menu_bar_(self):
		menu_bar = tkinter.Menu(self)	#继承原来Tk的Menu的对象
		file_menu = tkinter.Menu(menu_bar, tearoff = 0)
		file_menu.add_command(label='新建',accelerator = 'Ctrl+N', command=self.new_file)
		file_menu.add_command(label='打开',accelerator = 'Ctrl+O', command=self.open_file)
		file_menu.add_command(label='保存',accelerator = 'Ctrl+S')
		file_menu.add_command(label='另存为',accelerator = 'Ctrl+Shift+S')
		file_menu.add_separator()  #设置分割线
		file_menu.add_command(label='退出',accelerator = 'Alt+F4')
		menu_bar.add_cascade(label='文件',menu = file_menu) 	#创建文件的菜单栏
	
		#编辑菜单
		edit_menu = tkinter.Menu(menu_bar,tearoff = 0)  #基于菜单栏实例化“编辑”关联选项栏对象
		edit_menu.add_command(label='撤销',accelerator = 'Ctrl+Z')
		edit_menu.add_command(label='恢复',accelerator = 'Ctrl+Y')
		edit_menu.add_separator()
		edit_menu.add_command(label='剪切',accelerator = 'Ctrl+X')
		edit_menu.add_command(label='复制',accelerator = 'Ctrl+C')
		edit_menu.add_command(label='粘贴',accelerator = 'Ctrl+V')
		edit_menu.add_separator()
		edit_menu.add_command(label='查找',accelerator = 'Ctrl+F')
		edit_menu.add_separator()
		edit_menu.add_command(label='全选',accelerator = 'Ctrl+A')
	
		menu_bar.add_cascade(label='编辑',menu=edit_menu)  	#将“编辑”关联选项栏放在“编辑”菜单栏上
	
		#视图菜单
		view_menu = tkinter.Menu(menu_bar, tearoff = 0) #将“视图”关联选项栏放在“视图”菜单栏上
		self.show_line_number = tkinter.IntVar() 		#为了方便定义的这个变量在类中其他的函数中使用，这里将变量变成类中的实例属性
		self.show_line_number.set(1)
		view_menu.add_checkbutton(label='显示行号',variable=self.show_line_number)
	
		self.highlight_line = tkinter.IntVar()		#这里也是和上面一样，因为后面要用到这个变量
		view_menu.add_checkbutton(label='高亮当前行', onvalue = 1, offvalue = 0, variable = self.highlight_line)
	
		#在主题菜单中再添加一个子菜单
		theme_menu = tkinter.Menu(menu_bar, tearoff = 0)
		
		self.theme_choice = tkinter.StringVar()
		self.theme_choice.set('Default')
		for k in sorted(theme_color): 	#这里的theme_color就是之前从editor_style.py文件中导入的参数内容
			theme_menu.add_radiobutton(label=k,variable=self.theme_choice)
	
		view_menu.add_cascade(label='主题',menu=theme_menu) #注意这里添加的菜单栏指定的对象	
		menu_bar.add_cascade(label='视图', menu=view_menu)  #注意这里添加的菜单栏指定的对象	
	
		#关于菜单
		about_menu = tkinter.Menu(menu_bar, tearoff= 0)
		about_menu.add_command(label = '关于') #这里暂时未设置快捷键
		about_menu.add_command(label = '帮助') #一般是全局的快捷键，比如帮助的快捷键一般是F1
		menu_bar.add_cascade(label='关于',menu=about_menu)
		self['menu'] = menu_bar
		
	#在__init__函数下面要先添加这个函数，和之前创建_create_menu_bar_函数一样
	def _create_shortcut_bar_(self):
		shortcut_bar = tkinter.Frame(self, height=25, background='#20b2aa') #创建一个Frame放置快捷按钮
		shortcut_bar.pack(fill='x') #x轴方向填充
	
		for icon in ICONS:   #遍历循环设置快捷按钮
			img_file_path = './img/{}.png'.format(icon)
			print(img_file_path)
			pil_image = PIL.Image.open(img_file_path)   
			pil_image_resized = pil_image.resize((20, 20), PIL.Image.ANTIALIAS)
			tool_icon = PIL.ImageTk.PhotoImage(pil_image_resized)
			
			tool_btn = Button(shortcut_bar, image=tool_icon)
			#tool_btn.configure(width=10)
	
			tool_btn.pack(side='left')
			self.icon_res.append(tool_icon)#可以试试如果不设置类属性，运行后图标排列会是什么样子的
			
	#在__init__函数下面要先添加这个函数
	def _create_body_(self):
		#创建行号栏（takefocus屏蔽焦点）
		self.line_number_bar = tkinter.Text(self,width=4, padx=3, takefocus=0, border=0,
			background='#F0E68C',state='disabled')  #之后会使用这个变量，所以将其转换为实例属性
		self.line_number_bar.pack(side='left',fill='y')
	
		#创建文本输入框
		self.content_text = tkinter.Text(self, wrap = 'word')
		self.content_text.pack(expand='yes',fill='both')
	
		#创建滚动条
		scroll_bar = Scrollbar(self.content_text)
		scroll_bar['command'] = self.content_text.yview
		self.content_text['yscrollcommand'] = scroll_bar.set
		scroll_bar.pack(side='right',fill='y')

	#设置初始化窗口的属性
	def _set_window_(self):
		self.title("EditorPlus")              			     #窗口名称
		scn_width, scn_height = self.maxsize() 				 #获得程序运行机器的分辨率（屏幕的长和宽）
		wm_val = '750x450+{}+{}'.format((scn_width - 750) // 2, (scn_height - 450) // 2)
		self.geometry(wm_val) 				   				 #将窗口设置在屏幕的中间
		self.iconbitmap("img/editor.ico") 	  				 #加载一下窗口的左上方显示的图片
		self.protocol('WM_DELETE_WINDOW', self.exit_editor)  #设置窗口关闭提醒

	def exit_editor(self): 
		if messagebox.askokcancel('退出?','确定退出吗?'):      #设置文本提示框
			self.destroy() 									 #满足条件的话主窗口退出
			
	def new_file(self,event=None):
		self.title('New - EditorPlus')
		self.content_text.delete(1.0, tkinter.END)
		self.file_name = None
	def open_file(self,event=None):
		input_file = filedialog.askopenfilename(filetypes=[('所有文件','*.*'),('文本文档','*.txt')])  #弹出文件对话框，设置选择文件的类型
	
		if input_file:   			#如果用户选择了文本，则进行打开
			#print(input_file)   	#这里可以调试，看一下选中文本的路径的形式（绝对路径）
			self.title('{} - EditorPlus'.format(os.path.basename(input_file))) #以文件的名称进行窗口标题的命名
			self.file_name = input_file 	   #将这个打开的文件对象命名为其原来文件的名称
			self.content_text.delete(1.0, tkinter.END)  #删除当前文本内容中的数据
			with open(input_file, 'r') as _file:
				self.content_text.insert(1.0,_file.read())  #将要打开文件中的数据写入到文本内容中




if __name__ == '__main__':  #代码分块
	app = EditorPlus()      #类的实例化
	app.mainloop()			#程序运行
