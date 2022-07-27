# -*- coding: utf-8 -*-
"""
文 件 名: get_words_frome_picture.py
文件描述: 个人感觉识别率不高

增加图片处理库PIL
pip install Pillow
增加OCR识别库
pip install pytesseract

作    者: HanKin
创建日期: 2022.07.26
修改日期：2022.07.26

Copyright (c) 2022 HanKin. All rights reserved.
"""

#图库引用
from PIL import Image
#识别库引用
import pytesseract as pt
#图形界面引用
import tkinter as tk
#路径引用
import tkinter.filedialog as filedialog
#方法
class Application(tk.Tk):
    
    def __init__(self):
        super().__init__()
        self.title("图片文本提取")

        # r"" 的作用是去除转义字符
        pt.pytesseract.tesseract_cmd = r"C:\Program Files\Tesseract-OCR\tesseract.exe"
        #路径变量
        self.img_path = tk.StringVar()
        #布局
        self.frame = tk.Frame(self)
        self.frame.pack(padx=10, pady=10)
        #标签
        self.lbl_file = tk.Label(self.frame, text="图像")
        self.lbl_file.grid(row=0, column=0)
        #输入框布局
        self.txt_file = tk.Entry(self.frame, width=60, textvariable=self.img_path)
        self.txt_file.grid(row=0, column=1, sticky=tk.W)
        #button形式以及布局
        self.btn_file = tk.Button(self.frame, text="选择", command=self.sel_img_file)
        self.btn_file.grid(row=0, column=1, sticky=tk.E)
        #同上
        self.lbl_txt = tk.Label(self.frame, text="文本")
        self.lbl_txt.grid(row=1, column=0)        
        self.txt_exract = tk.Text(self.frame)
        self.txt_exract.grid(row=1, column=1)        
        self.btn_extract = tk.Button(self.frame, text="提取文本", command=self.extract_text)
        self.btn_extract.grid(row=2, column=1, sticky=tk.W+tk.E)        
        
    def sel_img_file(self):
        self.img_path.set(filedialog.askopenfilename(title="选择图片", initialdir="."))

    def extract_text(self):
        if self.img_path:
            img = Image.open(self.img_path.get())
            text = pt.image_to_string(img, lang="chi_sim")
            self.txt_exract.delete(1.0, tk.END)
            self.txt_exract.insert(tk.END, text)

if __name__ == "__main__":
    app = Application()
    app.mainloop()

