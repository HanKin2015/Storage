# -*- coding: utf-8 -*-
"""
Created on Wed Sep  2 11:34:11 2020

@author: Administrator
"""

#!/usr/bin/python3
# -*- coding: utf-8 -*-
 
import tkinter
import threading
import time
 
 
class section:
    def onPaste(self):
        print("显示AI机器人一天的工作")
 
    def onCopy(self):
        print("如果要现在开始工作，就点开始，否则会根据日常的安排工作")
 
    def onCut(self):
        print("学习新的工作技术，只要教过AI一次，就会了，以后的工作都可以交给他")
 
 
 
def move(event):
    global x,y,root
    new_x = (event.x-x)+root.winfo_x()
    new_y = (event.y-y)+root.winfo_y()
    s = "300x300+" + str(new_x)+"+" + str(new_y)
    root.geometry(s)
    print("当把我放到左上角200*200的区域时我会走人的,当前是x:%s,y:%s"%(new_x,new_y))
    if new_x<50 and new_y<50:
        exit()
    
def button_1(event):
    global x,y
    x,y = event.x,event.y
    print("event.x, event.y = ",event.x,event.y)
'右键菜单设置'
def button_3(event):
    global menu
    print(event.x_root, event.y_root)
    menu.post(event.x_root, event.y_root)
    '''
    global root
    root.Menu(root.abc,tearoff=0)
    root.Menu.post(event.x_root, event.y_root)
    '''
    
global x,y,root,menu
def aiui():
    global root,menu
    root = tkinter.Tk()
    root.overrideredirect(True)
    root.wm_attributes('-topmost',1)
    sw=root.winfo_screenwidth()
    sh=root.winfo_screenheight()
    root_x=sw-300
    root_y=sh-300-50
    root.attributes("-alpha", 0.4)#窗口透明度60 %
    
    root.geometry("300x300+%d+%d"%(root_x,root_y))
    
    canvas = tkinter.Canvas(root)
    canvas.configure(width = 300)
    canvas.configure(height = 300)
    #canvas.configure(bg = "red")
    canvas.configure(highlightthickness = 0)
    
    
    filename = tkinter.PhotoImage(file = "./image/teacher.png")
    canvas.create_image(150,150, image=filename)
    
    canvas.bind("<B1-Motion>",move)
    canvas.bind("<Button-1>",button_1)
    canvas.bind("<Button-3>",button_3)
    
    canvas.pack()
    
    
    section_obj = section()
    menu = tkinter.Menu(canvas,tearoff=0)
    menu.add_command(label="我的工作", command=section_obj.onCopy)
    menu.add_separator()
    menu.add_command(label="开始工作", command=section_obj.onPaste)
    menu.add_separator()
    menu.add_command(label="技能学习", command=section_obj.onCut)
    menu.add_separator()
    menu.add_command(label="退出", command=root.quit)  
    
    
    
    
    root.mainloop()
 
 
    
'''线程控制'''
exitFlag = 0
class threadControl(threading.Thread):
    def __init__(self,threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
        
    def run(self):
        print ("开始线程：" + self.name)
        if self.name=='aiui':
            aiui()
        print_time(self.name, self.counter, 5)
        print ("退出线程：" + self.name)
        
def print_time(threadName, delay, counter):
    while counter:
        if exitFlag:
            threadName.exit()
        time.sleep(delay)
        print ("%s: %s" % (threadName, time.ctime(time.time())))
        counter -= 1
        
    
if __name__ == '__main__':    
    thread1=threadControl(1,'thread_1',1)
    thread2=threadControl(2,'thread_2',2)
    aiui_obj=threadControl(3,'aiui',3)
    
    aiui_obj.start()
    
    thread1.start()
    thread2.start()
    thread1.join()
    thread2.join()
    
    aiui_obj.join()
    print ("退出主线程")
    