# 类的学习

## 1、魔法方法
https://blog.csdn.net/m0_66881249/article/details/128878537
https://baijiahao.baidu.com/s?id=1762485769871728635&wfr=spider&for=pc

魔法方法的官方名称为special method，指的是Python自带的，具有强大功能的，在一些特定情况下会被自动调用的方法，方法名一般以两个下划线开始，并且以两个下划线结束，Python中大致有100多个魔法方法。

- __init__方法相当于是构造函数
- __del__方法相当于是析构函数
- __str__()方法：定义对象的字符串表示，可以通过print(obj)打印该对象，也可以通过str(obj)方法得到该字符串表示
- __add__()方法：定义对象间的加法操作，可以使用+运算符进行操作，相当于是operator运算符重载
- __call__()方法：定义一个可调用的对象，使实例对象可以像函数一样被调用

demo见：D:\Github\Storage\python\study\class\magic_method.py

## 2、__dict__方法
https://blog.csdn.net/m0_57133702/article/details/120564391

a、类的静态函数、类函数、普通函数、全局变量以及一些内置的属性都是放在类__dict__里的
b、对象的__dict__中存储了一些self.xxx的一些东西
c、一些内置的数据类型是没有__dict__属性的，如：int, list, dict等这些常用的数据类型是没有__dict__属性的

demo见：D:\Github\Storage\python\study\class\magic_method.py
那是不是之前想知道调用的dll文件有哪些方法就使用这个呢？答案是不行。
```
print(my_dll.__dict__) ==>> {'_name': 'D:\\Users\\User\\Desktop\\ArithmeticsDll.dll', '_FuncPtr': <class 'ctypes.CDLL.__init__.<locals>._FuncPtr'>, '_handle': 1942880256}

print(dir(my_dll)) ==>> ['_FuncPtr', '__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattr__', '__getattribute__', '__getitem__', '__gt__', '__hash__', '__init__', '__init_subclass__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_func_flags_', '_func_restype_', '_handle', '_name']
```

## 3、