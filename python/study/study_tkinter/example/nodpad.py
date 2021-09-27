# -*- coding: utf-8 -*-
"""
Created on Wed Sep  2 13:30:46 2020

@author: Administrator
"""

import os #系统模块
from editor_style import theme_color, ICONS #这里就是从之前命名的文件中导入两个参数
from tkinter import filedialog, messagebox #这两个需要单独导入
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button #导入ttk模块中的指定几个组件
import tkinter
import PIL
from PIL import ImageTk

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
		self._create_right_popup_menu()
        
	def _create_menu_bar_(self):
		menu_bar = tkinter.Menu(self)	#继承原来Tk的Menu的对象
		
		file_menu = tkinter.Menu(menu_bar, tearoff = 0)
		file_menu.add_command(label='新建',accelerator = 'Ctrl+N', command=self.new_file)
		file_menu.add_command(label='打开',accelerator = 'Ctrl+O', command=self.open_file)
		file_menu.add_command(label='保存',accelerator = 'Ctrl+S', command=self.save)
		file_menu.add_command(label='另存为',accelerator = 'Ctrl+Shift+S', command=self.save_as)
		file_menu.add_separator()  #设置分割线
		file_menu.add_command(label='退出',accelerator = 'Alt+F4', command=self.exit_editor)
		menu_bar.add_cascade(label='文件',menu = file_menu) 	#创建文件的菜单栏
	
		#编辑菜单
		edit_menu = tkinter.Menu(menu_bar,tearoff = 0)  #基于菜单栏实例化“编辑”关联选项栏对象
		edit_menu.add_command(label='撤销',accelerator = 'Ctrl+Z',command = lambda : self.handle_menu_action('撤销'))
		edit_menu.add_command(label='恢复',accelerator = 'Ctrl+Y',command = lambda : self.handle_menu_action('恢复'))
		edit_menu.add_separator()
		edit_menu.add_command(label='剪切',accelerator = 'Ctrl+X',command = lambda : self.handle_menu_action('剪切'))
		edit_menu.add_command(label='复制',accelerator = 'Ctrl+C',command = lambda : self.handle_menu_action('复制'))
		edit_menu.add_command(label='粘贴',accelerator = 'Ctrl+V',command = lambda : self.handle_menu_action('粘贴'))
		edit_menu.add_separator()
		edit_menu.add_command(label='全选',accelerator = 'Ctrl+A',command = lambda : self.handle_menu_action('全选'))
		edit_menu.add_separator()
		edit_menu.add_command(label='查找',accelerator = 'Ctrl+F',command = self.find_text)
		menu_bar.add_cascade(label='编辑',menu=edit_menu)  	#将“编辑”关联选项栏放在“编辑”菜单栏上
	
		#视图菜单
		view_menu = tkinter.Menu(menu_bar, tearoff = 0) #将“视图”关联选项栏放在“视图”菜单栏上
		self.is_show_line_num = tkinter.IntVar() 		#为了方便定义的这个变量在类中其他的函数中使用，这里将变量变成类中的实例属性
		self.is_show_line_num.set(1)
		view_menu.add_checkbutton(label='显示行号', variable=self.is_show_line_num,
								  command=self._update_line_num)
		self.is_highlight_line = tkinter.IntVar()		#这里也是和上面一样，因为后面要用到这个变量
		view_menu.add_checkbutton(label='高亮当前行', onvalue=1, offvalue=0,
									  variable=self.is_highlight_line, command=self._toggle_highlight)  #通过checkbutton来实现功能
	
		#在主题菜单中再添加一个子菜单
		theme_menu = tkinter.Menu(menu_bar, tearoff = 0)
		self.theme_choice = tkinter.StringVar()
		self.theme_choice.set('Default')
		for k in sorted(theme_color): 	#这里的theme_color就是之前从editor_style.py文件中导入的参数内容
			theme_menu.add_radiobutton(label=k, variable=self.theme_choice, command=self.change_theme)
		view_menu.add_cascade(label='主题', menu=theme_menu) #注意这里添加的菜单栏指定的对象	
		menu_bar.add_cascade(label='视图', menu=view_menu)  #注意这里添加的菜单栏指定的对象	
	
		#关于菜单
		about_menu = tkinter.Menu(menu_bar, tearoff= 0)
		about_menu.add_command(label = '关于', command=lambda: self.show_messagebox('关于')) #这里暂时未设置快捷键
		about_menu.add_command(label = '帮助', command=lambda: self.show_messagebox('帮助')) #一般是全局的快捷键，比如帮助的快捷键一般是F1
		menu_bar.add_cascade(label='关于',menu=about_menu)
		#注意需要把帮助文档绑定为全局事件
		self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox("帮助"))
		
		self['menu'] = menu_bar				


	def show_messagebox(self, type):
		if type == "帮助":
			messagebox.showinfo("帮助", "这是帮助文档！", icon='question')
		else:
			messagebox.showinfo("关于", "EditorPlus_V0.1")

		
	#通过设置_update_line_num函数来实现主要的功能
	def _toggle_highlight(self):     #高亮函数
		if self.is_highlight_line.get():  #如果是选择高亮，进行下一步
			self.content_text.tag_remove("active_line", 1.0, "end")    #移除所有的标记
			self.content_text.tag_add("active_line", "insert linestart", "insert lineend+1c")
			#添加新标记
			self.content_text.after(200, self._toggle_highlight)  #递归，不断的检查是否高亮
		else:
			self.content_text.tag_remove("active_line", 1.0, "end")  #取消高亮		

	def change_theme(self):
		selected_theme = self.theme_choice.get()  #选取设定的主体颜色
		fg_bg = theme_color.get(selected_theme)   #包含了前景色和背景色
		fg_color, bg_color = fg_bg.split('.')     #提取颜色
		self.content_text.config(bg=bg_color, fg=fg_color)  #颜色设定

	def _update_line_num(self):
		if self.is_show_line_num.get():  #如果是选择了显示行号，进行下面的内容
			row, col = self.content_text.index("end").split('.')  #主要是获取行数
			line_num_content = "\n".join([str(i) for i in range(1, int(row))]) #获取文本行数据
			self.line_number_bar.config(state='normal')  #将文本栏状态激活
			self.line_number_bar.delete('1.0', 'end')    #删除原有的行号数据
			self.line_number_bar.insert('1.0', line_num_content) #插入行号文本数据
			self.line_number_bar.config(state='disabled') #再次封印行号栏
		else:  #如果不显示行号的话，进行下面的操作
			self.line_number_bar.config(state='normal')  #将文本栏状态激活
			self.line_number_bar.delete('1.0', 'end')  #删除原有的行号数据，这样就没有行号数据了
			self.line_number_bar.config(state='disabled') #再次封印行号栏
		
	#在__init__函数下面要先添加这个函数，和之前创建_create_menu_bar_函数一样
	def _create_shortcut_bar_(self):
		shortcut_bar = tkinter.Frame(self, height=25, background='#20b2aa') #创建一个Frame放置快捷按钮
		shortcut_bar.pack(fill='x') #x轴方向填充
	
		for icon in ICONS:   #遍历循环设置快捷按钮
			img_file_path = './img/{}.png'.format(icon)
			#print(img_file_path)
			pil_image = PIL.Image.open(img_file_path)   
			pil_image_resized = pil_image.resize((20, 20), PIL.Image.ANTIALIAS)
			tool_icon = PIL.ImageTk.PhotoImage(pil_image_resized)
			
			style = tkinter.ttk.Style()
			style.configure("BW.TLabel", foreground="black", background="white")
			tool_btn = Button(shortcut_bar, image=tool_icon, command=self._shortcut_action(icon), takefocus=False)
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
		self.content_text = tkinter.Text(self, wrap = 'word', undo =True)
		self.content_text.pack(expand='yes',fill='both')
		self.content_text.bind('<Control-N>', self.new_file)
		self.content_text.bind('<Control-n>', self.new_file)
		self.content_text.bind('<Control-O>', self.open_file)
		self.content_text.bind('<Control-o>', self.open_file)
		self.content_text.bind('<Control-S>', self.save)
		self.content_text.bind('<Control-s>', self.save)
		self.content_text.bind('<Control-Shift-S>', self.save_as)
		self.content_text.bind('<Control-Shift-s>', self.save_as)
		self.content_text.bind('<Alt-F4>', self.exit_editor)
		self.content_text.bind('<Control-F>', self.find_text)
		self.content_text.bind('<Control-f>', self.find_text)
		self.content_text.bind('<Any-KeyPress>', lambda e: self._update_line_num())
		self.content_text.tag_configure('active_line', background='#EEEEE0')
		self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox("帮助"))
	
		#创建滚动条
		scroll_bar = Scrollbar(self.content_text)
		scroll_bar['command'] = self.content_text.yview
		self.content_text['yscrollcommand'] = scroll_bar.set
		scroll_bar.pack(side='right',fill='y')

		
	def _create_right_popup_menu(self):
		popup_menu = tkinter.Menu(self.content_text, tearoff=0)
		for it1, it2 in zip(['剪切', '复制', '粘贴', '撤销', '恢复'],
							['cut', 'copy', 'paste', 'undo', 'redo']):
			popup_menu.add_command(label=it1, compound='left',
								   command=self._shortcut_action(it2))
		popup_menu.add_separator()
		popup_menu.add_command(label='全选', command = lambda: self.handle_menu_action("全选"))
		self.content_text.bind('<Button-3>',
							   lambda event: popup_menu.tk_popup(event.x_root, event.y_root))
		
	def _shortcut_action(self, type):
		def handle():
			if type == "new_file":
				self.new_file()
			elif type == "open_file":
				self.open_file()
			elif type == "save":
				self.save()
			if type == "cut":
				self.handle_menu_action("剪切")
			elif type == "copy":
				self.handle_menu_action("复制")
			elif type == "paste":
				self.handle_menu_action("粘贴")
			elif type == "undo":
				self.handle_menu_action("撤销")
			elif type == "redo":
				self.handle_menu_action("恢复")
			elif type == "find_text":
				self.find_text()
			if type != "copy" and type != "save":
				self._update_line_num()
		return handle #最后返回的是就是handle对象

	def handle_menu_action(self, action_type):
		if action_type == "撤销":
			self.content_text.event_generate("<<Undo>>")
		elif action_type == "恢复":
			self.content_text.event_generate("<<Redo>>")
		elif action_type == "剪切":
			self.content_text.event_generate("<<Cut>>")
		elif action_type == "复制":
			self.content_text.event_generate("<<Copy>>")
		elif action_type == "粘贴":
			self.content_text.event_generate("<<Paste>>")
		elif action_type == "全选":
			self.content_text.event_generate("<<SelectAll>>")
		if action_type != "复制":
			self._update_line_num()

		return 'break'

	def find_text(self,event=None):
		search_toplevel = tkinter.Toplevel(self)		#创建一个顶级窗口
		search_toplevel.title('查找文本')		#窗口命名
		search_toplevel.transient(self) 		#总是让搜索框显示在主程序窗口之上
		search_toplevel.geometry('340x60+700+500')
		search_toplevel.resizable(False, False) #窗口不可变
		Label(search_toplevel,text='查找全部：').grid(row=0,column=0,sticky='e')
		search_entry_widget = tkinter.Entry(search_toplevel,width=25)
		search_entry_widget.grid(row=0,column=1,padx=2,pady=2,sticky='we')
		search_entry_widget.focus_set()
	
		ignore_case_value = tkinter.IntVar()
		Checkbutton(search_toplevel, text='忽略大小写', variable=ignore_case_value).grid(
			row=1, column=1, sticky='e', padx=2, pady=2)
	
		Button(search_toplevel, text="查找", command=lambda: self.search_result(
			search_entry_widget.get(), ignore_case_value.get(), search_toplevel, search_entry_widget)
			   ).grid(row=0, column=2, sticky='e' + 'w', padx=2, pady=2)
	
		def close_search_window():
			self.content_text.tag_remove('match', '1.0', "end")
			search_toplevel.destroy()
	
		search_toplevel.protocol('WM_DELETE_WINDOW', close_search_window)
		return "break"
	
	def search_result(self, key, ignore_case, search_toplevel, search_box):
		self.content_text.tag_remove('match', '1.0', "end")
		print(ignore_case)#不勾选的话就是0，默认不忽略
		matches_found = 0
		if key:
			start_pos = '1.0'
			while True:
				# search返回第一个匹配上的结果的开始索引，返回空则没有匹配的（nocase：忽略大小写）
				start_pos = self.content_text.search(key, start_pos, nocase=ignore_case, stopindex="end")
				if not start_pos:
					break
				end_pos = '{}+{}c'.format(start_pos, len(key))
				self.content_text.tag_add('match', start_pos, end_pos)
				matches_found += 1
				start_pos = end_pos
			self.content_text.tag_config('match', foreground='red', background='yellow')
		search_box.focus_set()
		search_toplevel.title('发现%d个匹配的' % matches_found)
	
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
			self._update_line_num()

	def save(self, event=None):
		if not self.file_name:  #这里就体现出来之前设置的self.file_name全局变量的作用了
			self.save_as()      #没有有文件名称的另保存
		else:
			self._write_to_file(self.file_name)  #有文件名称的直接写入文件（保存本地）

	def save_as(self,event=None):
		input_file = filedialog.asksaveasfilename(        #注意这里弹出的是文件保存对话框
			filetypes = [('所有文件','*.*'),('文本文档','*.txt')]
			)
		if input_file:   						#还是要对用户操作进行判定
			self.file_name = input_file     	#设置文件名称
			self._write_to_file(self.file_name) #写入本地

	def _write_to_file(self, file_name):
		try:
			content = self.content_text.get(1.0, 'end')  #先获取文本框中的所有数据
			with open(file_name, 'w') as the_file:
				the_file.write(content)					 #将数据写入到本地的文件中
			self.title("%s - EditorPlus" % os.path.basename(file_name)) #这一步就是显示当前窗口的标题不变，可以尝试注释一下这行代码
		except IOError:    
			messagebox.showwarning("保存", "保存失败！")   #如果保存失败的话，会弹出消息对话框



if __name__ == '__main__':  #代码分块
	app = EditorPlus()      #类的实例化
	app.mainloop()			#程序运行
