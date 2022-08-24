# -*- coding: utf-8 -*-
"""
文 件 名: copy_tool.py
文件描述: 利用ftp库进行端与端之间拷贝的工具
作    者: HanKin
创建日期: 2020.11.01
修改日期：2022.08.15

Copyright (c) 2022 HanKin. All rights reserved.
"""

from common import *
from ftp_operation import *

class CopyTool(tkinter.Tk):
    '''主窗口ui类
    '''

    # tkinter的对话窗口必须要有一个主窗口，就像所有控件都需要放在一个窗口上。建立一个隐形窗口后就不会出现那个影响美观的自带窗口了
    # 解决多余的tk窗口
    root = tkinter.Tk()
    root.withdraw()

    my_ftp = MyFTP()

    def __init__(self):
        '''初始化自己的创建的CopyTool类
        '''

        super().__init__()          # 在继承Tk这个类的基础上在自己的类中添加内容
        self._generate_icon_()      # 生成图标
        self._set_window_()         # 设置程序运行主窗口
        self._create_menu_bar_()    # 创建菜单组件
        self._create_body_()        # 创建主体
        self._create_right_popup_menu()

    def _generate_icon_(self):
        tmp = open('copy_tool.ico', 'wb+')
        tmp.write(base64.b64decode(icon_img))
        tmp.close()

    def _set_window_(self):
        '''设置初始化窗口的属性
        '''

        self.title(app_name)  # 窗口名称
        self.resizable(False, False)
        # self.update()
        scn_width, scn_height = self.maxsize()  # 获得程序运行机器的分辨率（屏幕的长和宽）
        wm_val = '750x450+{}+{}'.format((scn_width - 750) //
                                        2, (scn_height - 450) // 2)
        self.geometry(wm_val)  # 将窗口设置在屏幕的中间
        self.iconbitmap('copy_tool.ico')  # 加载一下窗口的左上方显示的图片
        os.remove('copy_tool.ico')
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
        ftp_menu.add_command(
            label='设置FTP服务器', accelerator='Ctrl+F', command=self.set_ftp)
        ftp_menu.add_separator()  # 设置分割线
        ftp_menu.add_command(
            label='从本地上传', accelerator='Ctrl+U', command=self.upload_file)
        ftp_menu.add_command(
            label='从服务器下载', accelerator='Ctrl+D', command=self.down_file)
        ftp_menu.add_separator()  # 设置分割线
        ftp_menu.add_command(label='清理', accelerator='Ctrl+L',
                             command=self.delete_remote_dir)
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
        about_menu.add_command(label='更新日志', command=lambda: self.show_messagebox('更新日志'))  # 这里暂时未设置快捷键
        menu_bar.add_cascade(label='关于', menu=about_menu)
        # 注意需要把帮助文档绑定为全局事件
        self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox('帮助'))

        self['menu'] = menu_bar
        
    def set_ftp(self):
        '''设置FTP服务器
        '''
        
        self.set_ftp_window = tkinter.Toplevel(self)
        self.set_ftp_window.title('设置FTP服务器')
        window_width = 200
        window_hight = 100
        pos_x = self.winfo_rootx() + ((self.winfo_width() - window_width) // 2)
        pos_y = self.winfo_rooty() - 20 + ((self.winfo_height() - window_hight) // 2)
        wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, pos_x, pos_y)
        self.set_ftp_window.geometry(wm_val)       # 将窗口设置在屏幕的中间
        
        ip_label = tkinter.Label(self.set_ftp_window, text='ip地址：', justify=tkinter.LEFT)
        self.ip_entry = tkinter.Entry(self.set_ftp_window, text='')
        user_label = tkinter.Label(self.set_ftp_window, text='用户名：', justify=tkinter.LEFT)
        self.user_entry = tkinter.Entry(self.set_ftp_window, text='')
        pwd_label = tkinter.Label(self.set_ftp_window, text='密   码：', justify=tkinter.LEFT)
        self.pwd_entry = tkinter.Entry(self.set_ftp_window, text='')
        ip_label.grid(row=0, column=0)
        self.ip_entry.grid(row=0, column=1)
        user_label.grid(row=1, column=0)
        self.user_entry.grid(row=1, column=1)
        pwd_label.grid(row=2, column=0, sticky=tkinter.W)
        self.pwd_entry.grid(row=2, column=1, sticky=tkinter.W)
        
        qry_btn = tkinter.Button(self.set_ftp_window, text='确定', width=10, height=1,
                                      command=lambda: self.qry_btn_clicked(self.ip_entry, self.user_entry, self.pwd_entry), compound='right')
        qry_btn.grid(row=3, column=1, sticky=tkinter.E)
        
        self.set_ftp_window.mainloop()
        
    def qry_btn_clicked(self, ip_entry, user_entry, pwd_entry):
        '''设置FTP服务器确定按钮
        '''
        
        ip   = ip_entry.get().strip()
        user = user_entry.get().strip()
        pwd  = pwd_entry.get().strip()
        
        config = configparser.ConfigParser()
        if os.path.exists(config_path):
            config.read(config_path)
        
        if not config.has_section('ftp'):
            config.add_section('ftp')

        config.set('ftp', 'ip', ip)
        config.set('ftp', 'username', user)
        config.set('ftp', 'password', pwd)
        config.write(open(config_path, 'w'))
        
        logger.info('重新建立ftp连接')
        self.my_ftp.ftp_connect()
        
        self.set_ftp_window.destroy()
    
    def show_messagebox(self, type):
        '''
        '''
        
        content   = ''
        file_path = ''
        
        if type == '帮助':
            file_path = help_file_path
        elif type == '更新日志':
            file_path = update_file_path
        elif type == '关于':
            file_path = about_file_path
            
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read() 
        except Exception as ex:
            logger.error('打开文件失败, error={}'.format(ex))
        messagebox.showinfo(type, content, icon='question')

    # 通过设置_update_line_num函数来实现主要的功能
    def _toggle_highlight(self):  # 高亮函数
        if self.is_highlight_line.get():  # 如果是选择高亮，进行下一步
            self.content_text.tag_remove('active_line', 1.0, 'end')  # 移除所有的标记
            self.content_text.tag_add(
                'active_line', 'insert linestart', 'insert lineend+1c')
            # 添加新标记
            self.content_text.after(
                200, self._toggle_highlight)  # 递归，不断的检查是否高亮
        else:
            self.content_text.tag_remove('active_line', 1.0, 'end')  # 取消高亮

    def change_theme(self):
        selected_theme = self.theme_choice.get()  # 选取设定的主体颜色
        fg_bg = theme_color.get(selected_theme)  # 包含了前景色和背景色
        fg_color, bg_color = fg_bg.split('.')  # 提取颜色
        self.content_text.config(bg=bg_color, fg=fg_color)  # 颜色设定

    def _update_line_num_(self):
        if self.is_show_line_num.get():  # 如果是选择了显示行号，进行下面的内容
            row, col = self.content_text.index('end').split('.')  # 主要是获取行数
            line_num_content = '\n'.join(
                [str(i) for i in range(1, int(row))])  # 获取文本行数据
            self.line_number_bar.config(state='normal')  # 将文本栏状态激活
            self.line_number_bar.delete('1.0', 'end')  # 删除原有的行号数据
            self.line_number_bar.insert('1.0', line_num_content)  # 插入行号文本数据
            self.line_number_bar.config(state='disabled')  # 再次封印行号栏
        else:  # 如果不显示行号的话，进行下面的操作
            self.line_number_bar.config(state='normal')  # 将文本栏状态激活
            self.line_number_bar.delete('1.0', 'end')  # 删除原有的行号数据，这样就没有行号数据了
            self.line_number_bar.config(state='disabled')  # 再次封印行号栏

    def _create_body_(self):
        '''主体部分
        '''

        # 设置字体slant=tf.ITALIC,underline=1,overstrike=1,consolas
        ft = tkinter.font.Font(
            family=r'微软雅黑', weight=tkinter.font.NORMAL, size=12)

        # 上面部分
        fm_up = tkinter.Frame(self)
        # fm_up.propagate(0)
        self.input_content = EntryWithPlaceholder(fm_up, '请输入上传文件路径(可鼠标双击选择)', font=ft)
        #self.input_content = tkinter.Entry(fm_up, width=30, font=ft)
        self.input_content.pack(
            side=tkinter.LEFT, expand=True, fill=tkinter.X, padx=5, pady=5)

        # self.input_content.bind(sequence='<Button-1><ButtonRelease-1>', func=mourse_double_clicked)  #单击鼠标左键
        self.input_content.bind(
            sequence='<Double-Button-1><ButtonRelease-1>', func=self.mourse_double_clicked)  # 双击鼠标左键

        upload_btn = tkinter.Button(fm_up, text='发送', width=10, height=1,
                                    command=lambda: self.upload_btn_cliecked(self.content_text), font=ft, compound='center')
        upload_btn.pack(side=tkinter.LEFT, pady=5)
        download_btn = tkinter.Button(fm_up, text='接收', width=10, height=1,
                                      command=lambda: self.download_btn_cliecked(self.content_text), font=ft, compound='center')
        download_btn.pack(side=tkinter.LEFT, padx=5)

        fm_up.pack(fill=tkinter.X)

        # 中间部分
        fm_mid = tkinter.Frame(self)
        fm_mid.propagate(0)
        # 创建行号栏（takefocus屏蔽焦点）
        self.line_number_bar = tkinter.Text(fm_mid, width=3, padx=3, takefocus=0, border=0,
                                            background='#F0E68C', state='disabled', font=ft)  # 之后会使用这个变量，所以将其转换为实例属性
        self.line_number_bar.pack(side='left', fill='y')

        # 创建文本输入框
        self.content_text = tkinter.Text(
            fm_mid, wrap='word', undo=True, font=ft)
        self.content_text.pack(expand='yes', fill='both')
        self.content_text.bind('<Control-O>', self.open_file)
        self.content_text.bind('<Control-o>', self.open_file)
        self.content_text.bind('<Alt-F4>', self.exit_copy_tool)
        self.content_text.bind(
            '<Any-KeyPress>', lambda e: self._update_line_num_())
        self.content_text.tag_configure('active_line', background='#EEEEE0')
        self.bind_all('<KeyPress-F1>', lambda e: self.show_messagebox('帮助'))

        # 创建滚动条
        scroll_bar = Scrollbar(self.content_text)
        scroll_bar['command'] = self.content_text.yview
        self.content_text['yscrollcommand'] = scroll_bar.set
        scroll_bar.pack(side='right', fill='y')

        fm_mid.pack(fill=tkinter.BOTH, expand='yes')

        # 下面部分：拷贝按钮
        fm_down = tkinter.Frame(self)
        # fm_down.propagate(0)
        copy_btn = tkinter.Button(fm_down, text='拷贝文字', command=lambda: self.copy_btn_cliecked(
            self.content_text), font=ft, compound='center')
        copy_btn.pack(fill='both')
        fm_down.pack(fill='x')

    def _create_right_popup_menu(self):
        popup_menu = tkinter.Menu(self.content_text, tearoff=0)
        for it1, it2 in zip(['剪切', '复制', '粘贴', '撤销', '恢复'],
                            ['cut', 'copy', 'paste', 'undo', 'redo']):
            popup_menu.add_command(label=it1, compound='left',
                                                       command=self._shortcut_action(it2))
        popup_menu.add_separator()
        popup_menu.add_command(
            label='全选', command=lambda: self.handle_menu_action('全选'))
        self.content_text.bind('<Button-3>',
                               lambda event: popup_menu.tk_popup(event.x_root, event.y_root))

    def _shortcut_action(self, type):
        def handle():
            if type == 'new_file':
                self.new_file()
            elif type == 'open_file':
                self.open_file()
            elif type == 'save':
                self.save()
            if type == 'cut':
                self.handle_menu_action('剪切')
            elif type == 'copy':
                self.handle_menu_action('复制')
            elif type == 'paste':
                self.handle_menu_action('粘贴')
            elif type == 'undo':
                self.handle_menu_action('撤销')
            elif type == 'redo':
                self.handle_menu_action('恢复')
            elif type == 'find_text':
                self.find_text()
            if type != 'copy' and type != 'save':
                self._update_line_num_()
        return handle  # 最后返回的是就是handle对象

    def handle_menu_action(self, action_type):
        if action_type == '撤销':
            self.content_text.event_generate('<<Undo>>')
        elif action_type == '恢复':
            self.content_text.event_generate('<<Redo>>')
        elif action_type == '剪切':
            self.content_text.event_generate('<<Cut>>')
        elif action_type == '复制':
            self.content_text.event_generate('<<Copy>>')
        elif action_type == '粘贴':
            self.content_text.event_generate('<<Paste>>')
        elif action_type == '全选':
            self.content_text.event_generate('<<SelectAll>>')
        if action_type != '复制':
            self._update_line_num_()

        return 'break'

    def exit_copy_tool(self):
        '''退出提示框
        '''

        if messagebox.askokcancel('退出?', '确定退出吗?'):  # 设置文本提示框
            self.destroy()  # 满足条件的话主窗口退出
            self.root.destroy()
            self.my_ftp.ftp_disconnect()

    def new_file(self, event=None):
        self.title('New - CopyTool')
        self.content_text.delete(1.0, tkinter.END)
        self.file_name = None

    def open_file(self, event=None):
        input_file = filedialog.askopenfilename(
            filetypes=[('所有文件', '*.*'), ('文本文档', '*.txt')])  # 弹出文件对话框，设置选择文件的类型

        if input_file:  # 如果用户选择了文本，则进行打开
            # print(input_file)   	#这里可以调试，看一下选中文本的路径的形式（绝对路径）
            # 以文件的名称进行窗口标题的命名
            self.title('{} - CopyTool'.format(os.path.basename(input_file)))
            self.file_name = input_file  # 将这个打开的文件对象命名为其原来文件的名称
            self.content_text.delete(1.0, tkinter.END)  # 删除当前文本内容中的数据
            with open(input_file, 'r', encoding='utf-8') as _file:
                self.content_text.insert(
                    1.0, _file.read())  # 将要打开文件中的数据写入到文本内容中
            self._update_line_num_()

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

    def delete_remote_dir(self):
        # 做一下内容清理，防止磁盘爆满以及下载的不方便
        self.my_ftp.remove_dir(remote_dir_path)
        win32api.MessageBox(0, '清除完毕', '清空文件夹提醒', win32con.MB_OK)

    def send_assign_file(self):
        assign_file_path = self.input_content.get()
        if assign_file_path:
            assign_file_name = assign_file_path[assign_file_path.rfind('/')+1:]
            remote_file_path = remote_dir_path + assign_file_name
            self.my_ftp.upload_file(assign_file_path, remote_file_path)
            md5_value = md5.get_file_md5(assign_file_path)
            win32api.MessageBox(0, '发送指定文件成功\nmd5:{}'.format(
                md5_value), '发送文件提醒', win32con.MB_OK)

    def recv_assign_file(self):
        assign_file_path = self.input_content.get()
        if assign_file_path:
            assign_file_name = assign_file_path[assign_file_path.rfind('/')+1:]
            remote_file_path = remote_dir_path + assign_file_name
            self.my_ftp.download_file(assign_file_path, remote_file_path)
            md5_value = md5.get_file_md5(assign_file_path)
            win32api.MessageBox(0, '下载指定文件替换成功\nmd5:{}'.format(
                md5_value), '替换文件提醒', win32con.MB_OK)

    def upload_file(self):
        '''选择文件，并将文件上传到指定的文件夹中
        PS:首先要对文件夹进行清理
        '''

        input_file = filedialog.askopenfilename(  # 注意这里弹出的是文件保存对话框
            filetypes=[('所有文件', '*.*'), ('文本文档', '*.txt')]
        )
        if input_file:
            # 先清除内容
            self.input_content.delete(0, 'end')
            self.input_content.insert(0, input_file)
            file_name_index = input_file.rfind('/')
            logger.info(input_file[file_name_index+1:])
            file_name = input_file[file_name_index+1:]
            self.my_ftp.upload_file(input_file, remote_dir_path+file_name)
            md5_value = md5.get_file_md5(input_file)
            win32api.MessageBox(0, '上传成功\nmd5:{}'.format(
                md5_value), '上传文件提醒', win32con.MB_OK)

    def mourse_double_clicked(self, event):
        logger.info('mouse position is x={}, y={}'.format(event.x, event.y))
        input_file = filedialog.askopenfilename(  # 注意这里弹出的是文件保存对话框
            filetypes=[('所有文件', '*.*'), ('文本文档', '*.txt')]
        )
        if input_file:
            # 先清除内容
            self.input_content.delete(0, 'end')
            self.input_content.insert(0, input_file)

    def down_file(self):
        '''下载指定文件夹中的所有文件
        '''

        self.my_ftp.download_dir(download_path, remote_dir_path)
        # self.my_ftp.download_file('D:/Downloads/crawl_bing.py', 'VDI/hj/temp/crawl_bing.py')
        win32api.MessageBox(0, '全部下载完毕', '下载文件提醒', win32con.MB_OK)

    def _write_to_file(self, file_name):
        try:
            content = self.content_text.get(1.0, 'end')  # 先获取文本框中的所有数据
            with open(file_name, 'w') as the_file:
                the_file.write(content)  # 将数据写入到本地的文件中
            # 这一步就是显示当前窗口的标题不变，可以尝试注释一下这行代码
            self.title('%s - EditorPlus' % os.path.basename(file_name))
        except IOError:
            messagebox.showwarning('保存', '保存失败！')  # 如果保存失败的话，会弹出消息对话框

    def upload_btn_cliecked(self, display_content):
        '''
        发送按钮点击事件
        '''
        content = display_content.get('0.0', 'end').strip()
        file_path = work_path + temp_file_name
        logger.info('正在写入{}'.format(file_path))
        try:
            with open(file_path, 'w', encoding='utf-8') as f:
                f.write(content)
        except Exception as ex:
            logger.error('打开文件失败, error={}'.format(ex))

        self.my_ftp.upload_file(file_path, remote_dir_path+temp_file_name)
        # 提醒OK消息框
        win32api.MessageBox(0, '发送成功', '发送内容提醒', win32con.MB_OK)

    def download_btn_cliecked(self, display_content):
        '''
        接收消息按钮点击事件

        :param display_content:Text组件
        '''

        file_path = work_path + temp_file_name
        # print(file_path)
        ret = self.my_ftp.download_file(file_path, remote_dir_path+temp_file_name)
        logger.debug('ret = {}'.format(ret))
        if not ret:
            win32api.MessageBox(0, '接收失败', '接收内容提醒', win32con.MB_OK)
            return
        
        logger.info('正在读取{}'.format(file_path))
        content_list = []

        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content_list = f.readlines()
        except Exception as ex:
            logger.error('打开文件失败, error={}'.format(ex))

        content = ''
        for elem in content_list:
            content = content + elem

        display_content.delete('0.0', 'end')
        display_content.insert('insert', content)

    def copy_btn_cliecked(self, display_content):
        '''
        复制内容按钮点击事件
        '''

        # 打印显示内容
        content = display_content.get('0.0', 'end').strip()
        logger.info(content)

        # 将内容弄到剪切板
        display_content.event_generate('<<SelectAll>>')
        display_content.event_generate('<<Copy>>')


if __name__ == '__main__':
    app = CopyTool()    # 类的实例化
    app.mainloop()      # 程序运行
    logger.info('-----程序运行结束-----')
