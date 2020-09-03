# -*- coding: utf-8 -*-
"""
Created on Sat Aug 22 17:50:07 2020

@author: Administrator
"""

from tkinter import *

root=Tk()
texteditor=Text(root)
texteditor.pack(fill=BOTH)

def cut(event=None):
    global texteditor
    texteditor.event_generate("<<Cut>>")
def copy(event=None):
    
    global texteditor
    texteditor.event_generate("<<Copy>>")
def paste(event=None):
    texteditor.event_generate('<<Paste>>')
def select(event=None):
    texteditor.event_generate("<<SelectAll>>")

menubar=Menu(root)
filemenu=Menu(menubar)
root.config(menu=menubar)
filemenu.add_command(label="Cut",command=cut)
filemenu.add_command(label="Copy",command=copy)
filemenu.add_command(label="Paste",command=paste)
filemenu.add_command(label="Select",command=select)
menubar.add_cascade(label="File",menu=filemenu)
root.mainloop()