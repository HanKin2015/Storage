# -*- coding: utf-8 -*-
"""
Created on Thu Sep  3 13:16:42 2020

@author: Administrator
"""
import os
from editor_style import theme_color, ICONS
from tkinter import *
from tkinter import filedialog, messagebox
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button

class EditorPlus(Tk):
	icon_res = []
	file_name = None

	def __init__(self):
		super().__init__()
		self._set_window_()
		self._create_menu_bar_()
		self._create_shortcut_bar_()
		self._create_body_()
		self._create_right_popup_menu()

	def _set_window_(self):
		self.title("EditorPlus")
		scn_width, scn_height = self.maxsize()
		wm_val = '750x450+{}+{}'.format((scn_width - 750) // 2, 
										(scn_height - 450) // 2)
		self.geometry(wm_val)
		self.iconbitmap("img/editor.ico")
		self.protocol('WM_DELETE_WINDOW', self.exit_editor)

	def _create_menu_bar_(self):
		menu_bar = Menu(self)  #实例化菜单栏对象

		#文件菜单
		file_menu = Menu(menu_bar, tearoff = 0)  			#基于菜单栏实例化“文件”关联选项栏对象
		file_menu.add_command(label='新建',accelerator = 'Ctrl+N',command=self.new_file)
		file_menu.add_command(label='打开',accelerator = 'Ctrl+O',command=self.open_file)
		file_menu.add_command(label='保存',accelerator = 'Ctrl+S',command=self.save)
		file_menu.add_command(label='另存为',accelerator = 'Ctrl+Shift+S',command=self.save_as)
		file_menu.add_separator()
		file_menu.add_command(label='退出',accelerator = 'Alt+F4', command=self.exit_editor)

		menu_bar.add_cascade(label='文件',menu = file_menu) 	#将“文件”关联选项栏放在“文件”菜单栏上

		#编辑菜单
		edit_menu = Menu(menu_bar,tearoff = 0)  #基于菜单栏实例化“编辑”关联选项栏对象
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

		menu_bar.add_cascade(label='编辑',menu=edit_menu)  		#将“编辑”关联选项栏放在“编辑”菜单栏上

		#视图菜单
		view_menu = Menu(menu_bar, tearoff=0)
		self.is_show_line_num = IntVar()
		self.is_show_line_num.set(1)
		view_menu.add_checkbutton(label='显示行号', variable=self.is_show_line_num,
								  command=self._update_line_num)

		self.is_highlight_line = IntVar()
		view_menu.add_checkbutton(label='高亮当前行', onvalue=1, offvalue=0,
								  variable=self.is_highlight_line, command=self._toggle_highlight)

		#在主题菜单中再添加一个子菜单
		theme_menu = Menu(menu_bar, tearoff = 0)
		
		self.theme_choice = StringVar()
		self.theme_choice.set('Default')
		for k in sorted(theme_color): 			#这里的theme_color就是之前从editor_style.py文件中导入的参数内容
			theme_menu.add_radiobutton(label=k,variable=self.theme_choice,command=self.change_theme)

		view_menu.add_cascade(label='主题',menu=theme_menu) #注意这里添加的菜单栏指定的对象	
		menu_bar.add_cascade(label='视图', menu=view_menu)  #注意这里添加的菜单栏指定的对象	

		#关于菜单
		about_menu = Menu(menu_bar, tearoff= 0)
		about_menu.add_command(label='关于', command=lambda: self.show_messagebox('关于'))#这里暂时未设置快捷键
		about_menu.add_command(label='帮助', command=lambda: self.show_messagebox('帮助'))#一般是全局的快捷键，比如帮助的快捷键一般是F1
		menu_bar.add_cascade(label='关于',menu=about_menu)
		self['menu'] = menu_bar

	def show_messagebox(self, type):
		if type == "帮助":
			messagebox.showinfo("帮助", "这是帮助文档！", icon='question')
		else:
			messagebox.showinfo("关于", "EditorPlus_V0.1")

	def change_theme(self):
		selected_theme = self.theme_choice.get()
		fg_bg = theme_color.get(selected_theme)
		fg_color, bg_color = fg_bg.split('.')
		self.content_text.config(bg=bg_color, fg=fg_color)

	def _update_line_num(self):
		if self.is_show_line_num.get():
			row, col = self.content_text.index("end").split('.')
			line_num_content = "\n".join([str(i) for i in range(1, int(row))])
			self.line_number_bar.config(state='normal')
			self.line_number_bar.delete('1.0', 'end')
			self.line_number_bar.insert('1.0', line_num_content)
			self.line_number_bar.config(state='disabled')
		else:
			self.line_number_bar.config(state='normal')
			self.line_number_bar.delete('1.0', 'end')
			self.line_number_bar.config(state='disabled')

	def _toggle_highlight(self):
		if self.is_highlight_line.get():
			self.content_text.tag_remove("active_line", 1.0, "end")
			self.content_text.tag_add("active_line", "insert linestart", "insert lineend+1c")
			self.content_text.after(200, self._toggle_highlight)
		else:
			self.content_text.tag_remove("active_line", 1.0, "end")

	def _create_shortcut_bar_(self):
		shortcut_bar = Frame(self, height=25, background='#20b2aa')
		shortcut_bar.pack(fill='x')

		for icon in ICONS:
			tool_icon = PhotoImage(file='img/{}.png'.format(icon))
			tool_btn = Button(shortcut_bar, image=tool_icon,
							  command=self._shortcut_action(icon))
			tool_btn.pack(side='left')
			self.icon_res.append(tool_icon) #注意这里是创建一个全局变量，防止tool_icon（只是指向性的）被垃圾机制给干掉
											#这一点在没有创建类属性的时候是看的出来的，图片是不显示的

	def _create_body_(self):
		#创建行号栏（takefocus屏蔽焦点）
		self.line_number_bar = Text(self,width=4,padx =3,takefocus=0,border=0,
			background='#F0E68C',state='disabled')
		self.line_number_bar.pack(side='left',fill='y')

		#创建文本输入框
		self.content_text = Text(self, wrap='word',undo =True)
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
		popup_menu = Menu(self.content_text, tearoff=0)
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
			elif type == "cut":
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


	def new_file(self,event=None):
		self.title('New - EditorPlus')
		self.content_text.delete(1.0,END)
		self.file_name = None

	def open_file(self,event=None):
		input_file = filedialog.askopenfilename(
			filetypes=[('所有文件','*.*'),('文本文档','*.txt')])
		if input_file:
			print(input_file)
			self.title('{} - EditorPlus'.format(os.path.basename(input_file)))
			self.file_name = input_file
			self.content_text.delete(1.0,END)
			with open(input_file, 'r') as _file:
				self.content_text.insert(1.0,_file.read())

	def save(self,event=None):
		if not self.file_name:
			self.save_as()
		else:
			self._write_to_file(self.file_name)

	def save_as(self,event=None):
		input_file = filedialog.asksaveasfilename(
			filetypes = [('所有文件','*.*'),('文本文档','*.txt')]
			)
		if input_file:
			self.file_name = input_file
			self._write_to_file(self.file_name)

	def _write_to_file(self,file_name):
		try:
			content = self.content_text.get(1.0, END)
			with open(file_name,'w') as the_file:
				the_file.write(content)
			self.title('{} - EditorPlus'.format(os.path.basename(file_name)))
		except IOError:
			messagebox.showwarning('保存','保存失败！')

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
		search_toplevel = Toplevel(self)		#创建一个顶级窗口
		search_toplevel.title('查找文本')		#窗口命名
		search_toplevel.transient(self) 		#总是让搜索框显示在主程序窗口之上
		search_toplevel.geometry('340x60+700+500')
		search_toplevel.resizable(False, False) #窗口不可变
		Label(search_toplevel,text='查找全部：').grid(row=0,column=0,sticky='e')
		search_entry_widget = Entry(search_toplevel,width=25)
		search_entry_widget.grid(row=0,column=1,padx=2,pady=2,sticky='we')
		search_entry_widget.focus_set()

		ignore_case_value = IntVar()
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


	def exit_editor(self):
		if messagebox.askokcancel('退出?','确定退出吗?'):
			self.destroy()

if __name__ == '__main__':
	app = EditorPlus()
	app.mainloop()
