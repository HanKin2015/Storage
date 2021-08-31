# -*- coding: utf-8 -*-
"""
Created on Sat Aug 22 18:08:33 2020

@author: Administrator
"""

# encoding: utf-8
 
from tkinter import *
 
def printentry(event):
    print("click on", event.x, event.y)
    print(entry.get())
    print(len(entry.get()))
    entry.insert(len(entry.get()),"abc")
    entry.selection_range(0, len(entry.get()))
 
root=Tk()
var=StringVar()
var.set("int")
entry = Entry(root,text="")
entry.place(x=0, y=0, anchor=NW)
entry = Entry(root,textvariable=var)
entry.place(x=0, y=20, anchor=NW)
# entry.bind(sequence="<Button-1>", func=printentry)   #光单击鼠标左键不响应事件，它需要一个释放鼠标左键的事件来触发事件
entry.bind(sequence="<Button-1><ButtonRelease-1>", func=printentry)  #单击鼠标左键
# entry.bind(sequence="<Double-Button-1><ButtonRelease-1>", func=printentry)  #双击鼠标左键
root.mainloop()