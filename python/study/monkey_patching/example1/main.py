import monkey  # 导入用到的别人写的monkey模块

def i_am_human(self):  # 定义一个我们想要的方法
    print("I am human")

print(f"{monkey.Me.who_am_i = }")   # 替换前，将原来的方法地址打印出来
monkey.Me.who_am_i = i_am_human     # 将"who_am_i"的地址替换为"i_am_human"
print(f"{monkey.Me.who_am_i = }")   # 替换后，将原来的方法地址打印出来

obj = monkey.Me()  # 实例化一个对象

print(f"{hasattr(obj, 'i_am_human') = }")
print(f"{hasattr(obj, 'who_am_i') = }")
obj.who_am_i()  # 直接调用 "who_am_i" 而不是 "i_am_human()"

"""
在 print(f"{monkey.Me.who_am_i = }") 和 print(f"{monkey.Me.who_am_i = }") 这两行代码中，使用了 f-string 的新特性，即在字符串中使用 = 来打印变量名和值。这是 Python 3.8+ 的语法，如果你的 Python 版本低于 3.8，这些行会引发 SyntaxError。如果你的 Python 版本低于 3.8，请将这两行代码修改为普通的打印语句。

monkey.Me.who_am_i = <function Me.who_am_i at 0x7ff6ab1d9af0>
monkey.Me.who_am_i = <function i_am_human at 0x7ff6ab2a0310>
hasattr(obj, 'i_am_human') = False
hasattr(obj, 'who_am_i') = True
I am human
"""