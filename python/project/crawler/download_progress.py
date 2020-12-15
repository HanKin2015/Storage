import tkinter
import os  #导入库
from tkinter.ttk import Scrollbar, Checkbutton, Label, Button
import time
import threading
 
class Application(tkinter.Frame):

    def __init__(self, master=None):
        tkinter.Frame.__init__(self, master)    #调用父类的构造函数
        self._set_window_()     # 设置程序运行主窗口
        self._create_body_()    # 创建主体

    def _set_window_(self):
        self.master.title('下载进度')
        window_width = 600
        window_hight = 400
        self.screen_width, self.screen_height = self.master.maxsize()  # 获得程序运行机器的分辨率（屏幕的长和宽）
        print('{}x{}'.format(self.screen_width, self.screen_height))
        wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, (self.screen_width - window_width) //
                                        2, (self.screen_height - window_hight) // 2)
        self.master.geometry(wm_val)       # 将窗口设置在屏幕的中间
        self.master.resizable(0, 0)
    
    def _create_body_(self):
        '''
        '''
        # 上面部分
        frame_up = tkinter.Frame(self.master)
        frame_up.propagate(0)
        frame_up.pack(fill=tkinter.X)
        
        tkinter.Label(frame_up, text='下载进度:', ).grid(row=0, column=0)
        # 定义变量,必须是使用的是tk里的这个变量
        self.progress_value = tkinter.StringVar()
        self.progress_value.set('0%')
        tkinter.Label(frame_up, textvariable=self.progress_value).grid(row=0, column=1)
        
        '''
        进度条学习：
        mode: determinate/indeterminate
        orient(进度条的方向): HORIZONTAL/VERTICAL
        cursor: 鼠标位于进度条内时的形状
        length: 进度条长度
        maximum: 进度条最大刻度值
        style: 定义进度条的外观
        takefocus: 是否可以通过Tab获得输入焦点
        variable: 与进度条关联的变量。可以设置或获得进度条的当前值
        value: 设置或者获取进度条的当前值
        start(interval=None): 默认间隔是50毫秒。
        step(amount=None): 默认是1.0
        stop()
        '''
        
        # 进度条样式
        style = tkinter.ttk.Style()
        style.theme_use('alt')
        style.configure('blue.Horizontal.TProgressbar',
                        troughcolor  = '#4d4d4d',
                        troughrelief = 'flat',
                        background   = '#2f92ff')
        self.val = tkinter.IntVar(frame_up) # 这个能解决进度条停止后变为0的问题
        self.pb = tkinter.ttk.Progressbar(frame_up, length=400, style='blue.Horizontal.TProgressbar', orient='horizontal',maximum=100, value=0, mode="determinate", variable=self.val)
        self.pb.grid(row=1, column=0, columnspan=2)
        
        tkinter.Label(frame_up, text='下载成功数:', ).grid(row=0, column=3)
        tkinter.Label(frame_up, text='100', ).grid(row=0, column=4)
        tkinter.Label(frame_up, text='下载失败数:', ).grid(row=1, column=3)
        tkinter.Label(frame_up, text='0', ).grid(row=1, column=4)
        
        self.start_btn = tkinter.Button(frame_up, text="开始", command=self.start)
        self.start_btn.grid(row=1, column=5)
        
        # 下面部分
        frame_down = tkinter.Frame(self.master)
        #frame_down.propagate(0)
        frame_down.pack(fill=tkinter.BOTH, expand='yes')
        # 创建表格
        columns = ('编号', '时间', '图片名称', '图片大小', '图片类型', '图片状态')
        self.task_table = tkinter.ttk.Treeview(frame_down, show = "headings", columns = columns, selectmode = tkinter.BROWSE)
        
        for column in columns:
            print(column)
            self.task_table.column(column, width = 50, anchor = 'center')
            self.task_table.heading(column, text = column)
        
        self.task_table.pack(expand='yes', fill='both')
        
        # 创建滚动条
        scroll_bar = Scrollbar(self.task_table)
        scroll_bar['command'] = self.task_table.yview
        self.task_table['yscrollcommand'] = scroll_bar.set
        scroll_bar.pack(side='right', fill='y')
        
    def start(self):
        def real_traitement():
            self.pb.step(amount=5.0)
            self.pb.start(interval=500)
            while True:
                val = self.val.get()
                self.progress_value.set('{}%'.format(val))
                if val >= 98:
                    break
                time.sleep(1)
                
            self.pb.stop()
            #self.pb.grid_forget()
            self.start_btn['state']='normal'
            
        self.start_btn['state']='disabled'
        threading.Thread(target=real_traitement).start()

def download_progress(master=None):
    if master == None:
        root = tkinter.Tk()
    else:
        root = tkinter.Toplevel()   #创建一个Tk根窗口组件
    app = Application(master=root)
    app.mainloop()              # 程序运行   
    
if __name__ == '__main__':
    download_progress()
        
        
        
        
        