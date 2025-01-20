# -*- coding: utf-8 -*-
"""
文 件 名: class_inherit_global_variable.py
文件描述: 类的继承想定义一个全局变量，让所有的类对象使用同一个变量值
作    者: HanKin
备    注: 
创建日期: 2025.01.08
修改日期：2025.01.08

Copyright (c) 2025 HanKin. All rights reserved.
"""
class Common:
    def __init__(self):
        self.PASSWD = 0

    def set_passwd(self, passwd):
        self.PASSWD = passwd
   
# 定义一个父类（基类）
class Animal:
    common = Common()
    def __init__(self):
        #self.common = Common() # 这种方式达不到想要的结果
        pass

    def speak(self):
        return "Some sound"

# 定义一个子类（派生类），继承自 Animal
class Dog(Animal):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def speak(self):
        return "Woof!"

# 定义另一个子类，继承自 Animal
class Cat(Animal):
    def __init__(self, name):
        super().__init__()
        self.name = name
    def speak(self):
        return "Meow!"

# 修改全局变量
Animal().common.set_passwd(12345)

# 创建 Dog 和 Cat 的实例
dog = Dog("Buddy")
cat = Cat("Whiskers")

# 调用 speak 方法
print(f"{dog.name} says: {dog.speak()}")  # 输出: Buddy says: Woof!
print(f"{cat.name} says: {cat.speak()}")  # 输出: Whiskers says: Meow!

print(dog.common.PASSWD)
print(cat.common.PASSWD)