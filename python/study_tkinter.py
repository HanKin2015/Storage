# -*- coding: utf-8 -*-
"""
Created on Thu Aug 13 13:43:01 2020

@author: Administrator
"""


import tkinter as tk
 
root = tk.Tk()
 
text = tk.Text(root)
text.pack()
 
# "insert" 索引表示插入光标当前的位置
text.insert("insert", "I love ")
text.insert("end", "Python.com!")
 
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
    root = tkinter.Tk(className='Here is some interpretation')  # 弹出框框名
    root.geometry('800x600')     # 设置弹出框的大小 w x h

    var = tkinter.StringVar()   # 这即是输入框中的内容
    var.set(content) # 通过var.get()/var.set() 来 获取/设置var的值
    entry1 = tkinter.Entry(root, textvariable=var, width=50)  # 设置"文本变量"为var
      
    
    entry1.pack()   # 将entry"打上去"
    btn1 = tkinter.Button(root, text='Input', command=inputint)     # 按下此按钮(Input), 触发inputint函数
    btn2 = tkinter.Button(root, text='Clear', command=inputclear)   # 按下此按钮(Clear), 触发inputclear函数

    # 按钮定位
    btn2.pack(side='right')
    btn1.pack(side='right')

    # 上述完成之后, 开始真正弹出弹出框
    root.mainloop()