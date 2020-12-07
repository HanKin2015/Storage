import tkinter as tk,os  #导入库
from PIL import ImageTk,Image

class Application(tk.Frame):   #定义GUI的应用程序类，派生于Frmae
    img_max_width = 800
    img_max_height = 500

    def __init__(self,master=None):   #构造函数，master为父窗口
    
        self.files=os.listdir(r'./image/')   #获取图像文件名列表
        self.index=0    #图片索引，初始显示第一张
        print(self.files)
        #self.img=tk.PhotoImage(file=r'./image/'+self.files[self.index])
        img_pil = Image.open(r'./image/'+self.files[self.index])
        if img_pil.size[0] > self.img_max_width or img_pil.size[1] > self.img_max_height:
            img_pil = img_pil.resize((self.img_max_width, self.img_max_height))
        self.img = ImageTk.PhotoImage(img_pil)
        tk.Frame.__init__(self,master)    #调用父类的构造函数
        self.pack()  #调整显示的位置和大小
        self.createWidget()  #类成员函数，创建子组件
        
    def createWidget(self):
        self.lblImage=tk.Label(self,width=self.img_max_width,height=self.img_max_height+50)  #创建Label组件以显示图像
        self.lblImage['image']=self.img    #显示第一张照片
        self.lblImage.pack()   #调整显示位置和大小
        self.f=tk.Frame(self)   #创建窗口框架
        self.f.pack()
        self.btnPrev=tk.Button(self.f,text="上一张",command=self.prev)  #创建按钮
        self.btnPrev.pack(side=tk.LEFT)
        self.btnNext=tk.Button(self.f,text="下一张",command=self.next)  #创建按钮
        self.btnNext.pack(side=tk.LEFT)
        
    def prev(self):  #事件处理函数
        self.showfile(-1)
        
    def next(self):   #事件处理函数
        self.showfile(1)
        
    def showfile(self,n):
        self.index += n
        if self.index<0:
            self.index=len(self.files)-1    #循环显示最后一张
        if self.index>len(self.files)-1:
            self.index=0    #循环显示第一张
        #self.img=tk.PhotoImage(file=r'f:\jpg'+'\\'+self.files[self.index])
        img_pil = Image.open(r'./image/'+self.files[self.index])
        #print(img_pil.size)
        #print(img_pil.size[0])
        if img_pil.size[0] > self.img_max_width or img_pil.size[1] > self.img_max_height:
            img_pil = img_pil.resize((self.img_max_width, self.img_max_height))
        self.img = ImageTk.PhotoImage(img_pil)
        
        self.lblImage['image']=self.img
 
def picture_browser(master=None):
    if master == None:
        root = tk.Tk()
    else:
        root = tk.Toplevel()   #创建一个Tk根窗口组件
    root.title("简单图片浏览器")   #设置窗口标题
    window_width = 900
    window_hight = 600
    screen_width, screen_height = root.maxsize()
    wm_val = '{}x{}+{}+{}'.format(window_width, window_hight, (screen_width - window_width) //
                                    2, (screen_height - window_hight) // 2)
    root.geometry(wm_val)       # 将窗口设置在屏幕的中间
    app=Application(master=root)   #创建Application的对象实例
    app.mainloop()   #事件循环

if __name__ == '__main__':
    picture_browser()