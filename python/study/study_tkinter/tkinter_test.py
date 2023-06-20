from tkinter import *
# Tk\ Label\ Frame\ LEFT\ RIGHT\ Button\ PhotoImage\

# 示例 1:
"""
window=Tk()   #Tk()前不加模块name.
window.title('My Window')
window.geometry('600x800')  
# Label(text='123').pack()  #控件前不加模块name.
Label(window, text='我的第一个窗口').pack()
window.mainloop()
"""


# 示例 2:
"""
class APP:
	def __init__(self, master):#root 传参赋值给master
		frame = Frame(master)#frame 组件
		frame.pack(side=LEFT, padx=10, pady=10)
		#Button按钮, command中调用定义的方法
		self.hi_there = Button(frame, text='打招呼', bg='black', fg='white', command=self.say_hi)
		self.hi_there.pack()
	def say_hi(self):
		print('卧槽，居然打了个招呼！~')
root = Tk()
app = APP(root)
root.mainloop()
"""


# 示例 3:
root = Tk()
textLabel = Label(root, text='请重试！\n您的操作不被允许！', justify=LEFT, padx=10, pady=10)
# text文字支持换行、 justify左对齐、 padx左边距10px、 pady右边距10px
textLabel.pack(side=LEFT)
photo = PhotoImage(file=r"D:\Users\Sangfor\Desktop\123.png")#显示图片 需安装 Pillow 模块
imageLabel = Label(root, image=photo)
imageLabel.pack(side=RIGHT)
mainloop()

