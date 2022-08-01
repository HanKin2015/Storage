# -*- coding: utf-8 -*-
"""
Created on Thu Aug 13 13:43:01 2020

@author: hankin
@description:
    study tkinter
"""

# load modules
import tkinter as tk
import tkinter.font as tf
import win32api,win32con

def tkinter_exam1():
    '''example1
    tkinter base
    '''
    # main window
    root = tk.Tk()
    
    # window title
    root.title('hankin')
    
    # x and y can change(1-true,0-false)
    root.resizable(1, 0)
    
    # window size
    root.geometry('250x150')
    
    # close window
    root.quit()
    
    # flush window
    root.update()
    
    text = tk.Text(root)
    text.pack()
     
    # "insert" 索引表示插入光标当前的位置
    text.insert('insert', 'I love ')
    text.insert('end', 'Python.com!')
     
    root.mainloop()

global label

def tkinter_exam2():
    '''example2
    study components
    '''
    root = tk.Tk()
    root.title('study components')
    root.geometry('250x150')
    
    global label
    label=tk.Label(root,text='Hello')
    label.pack()        
    button1=tk.Button(root,text='Button1', command=button1_cliecked) 
    button1.pack(side=tk.LEFT)        
    button2=tk.Button(root,text='Button2', command=button2_cliecked)
    button2.pack(side=tk.RIGHT)
    bm = tk.PhotoImage(file='../image/pen.png')
    img = tk.Label(root, image = bm)
    img.pack(side=tk.BOTTOM)
    root.mainloop()            

def button1_cliecked():
    '''
    button click event
    '''
    content = label.cget('text')
    if content == 'Hello':
        print('yes')
    else:
        print('no')
def button2_cliecked():
    '''
    button click event
    '''
    label.configure(text='jk')


def set_win_center(root, cur_width='', cur_height=''):
    '''
    设置窗口大小，并居中显示
    :param root:主窗体实例
    :param cur_width:窗口宽度，非必填，默认200
    :param cur_height:窗口高度，非必填，默认200
    :return:无
    '''
    if not cur_width:
        '''获取窗口宽度，默认200'''
        cur_width = root.winfo_width()
    if not cur_height:
        '''获取窗口高度，默认200'''
        cur_height = root.winfo_height()
    # print(cur_width, cur_height)

    # 获取屏幕宽度和高度
    scn_w, scn_h = root.maxsize()
    # print(scn_w, scn_h)

    # 计算中心坐标
    cen_x = (scn_w - cur_width) / 2
    cen_y = (scn_h - cur_height) / 2
    # print(cen_x, cen_y)

    # 设置窗口初始大小和位置
    size_xy = '%dx%d+%d+%d' % (cur_width, cur_height, cen_x, cen_y)
    root.geometry(size_xy)

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

def upload_btn_cliecked():
    # 提醒OK消息框
    win32api.MessageBox(0, "上传成功", "提醒", win32con.MB_OK)

def download_btn_cliecked(display_content):
    display_content.SelectAll()
    
    
def copy_btn_cliecked(display_content):
    # 打印显示内容
    content = display_content.get('0.0', 'end').strip()
    print(content)
    
    # 将内容弄到剪切板
    display_content.event_generate("<<SelectAll>>")
    display_content.event_generate("<<Copy>>")

def send_recv_msg():
    '''
    send and recive message, intranet extranet
    '''
    root = tk.Tk()
    root.title('copy tool')
    root.resizable(False, False)
    root.update()
    set_win_center(root, 600, 600)
    
    # 设置字体slant=tf.ITALIC,underline=1,overstrike=1
    ft = tf.Font(family='consolas', weight=tf.BOLD, size=12)  
    
    # 上面部分
    fm_up = tk.Frame()
    input_content = tk.Entry(fm_up, width=30, font=ft)
    input_content.pack(side=tk.LEFT, expand=True, fill=tk.X, padx=5, pady=5)
    upload_btn = tk.Button(fm_up,text='send', width=10, height=1,\
                           command=upload_btn_cliecked, font=ft, compound='center') 
    upload_btn.pack(side=tk.LEFT, pady=5)     
    download_btn = tk.Button(fm_up,text='recive', width=10, height=1,\
                             command=lambda:download_btn_cliecked(display_content), font=ft, compound='center') 
    download_btn.pack(side=tk.LEFT, padx=5) 
    
    fm_up.pack(fill=tk.X)
    
    # 下面部分：显示内容和拷贝按钮
    fm_down = tk.Frame()
    display_content = tk.Text(fm_down, font=ft)
    display_content.pack(side=tk.TOP, fill=tk.Y, expand=True, padx=5)
    
    copy_btn = tk.Button(fm_down,text='copy', command=lambda:copy_btn_cliecked(display_content), font=ft, compound='center') 
    copy_btn.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5)
    fm_down.pack(fill=tk.BOTH, expand=True)
    
    root.mainloop()
    

def pop_up_box(content):
    """
    使用tkinter弹出输入框输入数字, 具有确定输入和清除功能, 可在函数内直接调用num(文本框的值)使用
    """
    
    def inputint():
        nonlocal num
        try:
            num = int(var.get().strip())
        except:
            num = 'Not a valid integer.'


    def inputclear():
        nonlocal num
        var.set('')
        num = ''

    num = 0
    root = tk.Tk(className='Here is some interpretation')  # 弹出框框名
    root.geometry('800x600')     # 设置弹出框的大小 w x h

    var = tk.StringVar()   # 这即是输入框中的内容
    var.set(content) # 通过var.get()/var.set() 来 获取/设置var的值
    entry1 = tk.Entry(root, textvariable=var, width=50)  # 设置"文本变量"为var
      
    
    entry1.pack()   # 将entry"打上去"
    btn1 = tk.Button(root, text='Input', command=inputint)     # 按下此按钮(Input), 触发inputint函数
    btn2 = tk.Button(root, text='Clear', command=inputclear)   # 按下此按钮(Clear), 触发inputclear函数

    # 按钮定位
    btn2.pack(side='right')
    btn1.pack(side='right')

    # 上述完成之后, 开始真正弹出弹出框
    root.mainloop()
    
if __name__ == "__main__":
    #tkinter_exam1()
    #tkinter_exam2()
    send_recv_msg()
    
    
    
    
    
    
    
    
    