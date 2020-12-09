import tkinter
import os  #导入库
 

def start(self):
    def real_traitement():
        self.pb.step(amount=5.0)
        self.pb.start(interval=500)
        while True:
            val = self.val.get()
            self.progress_value.set('{}%'.format(val))
            if val >= 50:
                break
            time.sleep(1)
            
        self.pb.stop()
        self.pb.grid_forget()
        self.start_btn['state']='normal'
        
    self.start_btn['state']='disabled'
    threading.Thread(target=real_traitement).start()

def download_progress(self):
    top = tkinter.Toplevel()
    top.title('进度条')
    window_width = 600
    window_hight = 150
    wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, (self.screen_width - window_width) //
                                    4, (self.screen_height - window_hight) // 2)
    top.geometry(wm_val)       # 将窗口设置在屏幕的中间
    
    
    tkinter.Label(top, text='下载进度:', ).place(x=50, y=60)
    # 定义变量,必须是使用的是tk里的这个变量
    self.progress_value = tkinter.StringVar()
    self.progress_value.set('0%')
    tkinter.Label(top, textvariable=self.progress_value).place(x=50, y=90)
    
    # 设置窗口图标
    #top.iconbitmap("./image/icon.ico")
    # 设置窗口宽高固定
    top.resizable(0, 0)
    
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
    self.val = tkinter.IntVar() # 这个能解决进度条停止后变为0的问题
    self.pb = tkinter.ttk.Progressbar(top, length=400, style='blue.Horizontal.TProgressbar', orient='horizontal',maximum=100, value=0, mode="determinate", variable=self.val)
    self.pb.pack(pady = 10)
    self.start_btn = tkinter.Button(top, text="开始", command=self.start)
    self.start_btn.pack()
    
    top.mainloop()

if __name__ == '__main__':
    download_progress()     
        
        
        
        
        