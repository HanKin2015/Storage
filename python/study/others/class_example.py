# -*- coding: utf-8 -*-
"""
文 件 名: class_example.py
文件描述: 学习类的定义和使用
作    者: HanKin
创建日期: 2023.12.02
修改日期：2023.12.02

Copyright (c) 2023 HanKin. All rights reserved.
"""
class Person:
    def __init__(self, name):
        self.name = name


    def greet(self):
        print("Hello, my name is " + self.name)


person = Person("John")
person.greet()  # Hello, my name is John

# 继承和多态
class Animal:
    def sound(self):
        pass

class Dog(Animal):
    def sound(self):
        print("Woof!")

class Cat(Animal):
    def sound(self):
        print("Meow!")

dog = Dog()
cat = Cat()
dog.sound() # Woof!
cat.sound() # Meow!