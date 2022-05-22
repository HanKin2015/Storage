from tkinter import *
from PIL import Image, ImageTk

win = Tk()      # 创建窗口对象
win.title("我的窗口")   # 设置窗口标题
lab1 = Label(win, text = '你好', anchor = 'nw') # 创建Label组件
lab1.pack()     # 显示Label组件

# 显示内置的位图
lab2 = Label(win, bitmap = 'question')  # 创建显示疑问图标的Label组件
lab2.pack()     # 显示Label组件

# 显示自选的图片
bm = ImageTk.PhotoImage(file = r'turtle.jpeg')
lab3 = Label(win, image = bm)
lab3.bm = bm
lab3.pack()     # 显示Label组件
win.mainloop()