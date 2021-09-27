# 记事本的实现

找到一个不学习python错的博客：https://blog.csdn.net/lys_828/article/list/2?t=1

## 1、实现一个记事本

https://blog.csdn.net/lys_828/article/details/105345014


##２、在给按钮添加图片时遇到问题
图片需要调整大小，因此使用PIL库对图片resize。然而由于一个PIL.ImageTk.PhotoImage和tkinter.PhotoImage的区别导致了一系列的不成功。
迁移代码需要仔细仔细再仔细。

## 3、注意
ttk 美化了Tkinter，但是也省略了一些属性。
比如不识别bg bd等属性。
_tkinter.TclError: unknown option "-bg"

## 4、AttributeError: module 'PIL' has no attribute 'ImageTk'
时而报错时而正常。保险的方法就是添加from PIL import ImageTk













