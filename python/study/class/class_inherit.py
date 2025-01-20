# -*- coding: utf-8 -*-
"""
文 件 名: class_inherit.py
文件描述: 类的继承
作    者: HanKin
备    注: 
创建日期: 2025.01.08
修改日期：2025.01.08

Copyright (c) 2025 HanKin. All rights reserved.
"""
import json

# 动态配置：如果配置文件可能会在运行时更改，或者你需要处理加载过程中的错误，使用实例属性的方式更为合适
class Father1:
    def __init__(self):
        with open(r"D:\Demo\device_helper\config\device_helper.config", encoding='utf-8') as f:
            self.CONFIG = json.load(f)
class Son1(Father1):
    def __init__(self):
        super().__init__()  # 调用父类的构造函数
        print(self.CONFIG["BOX_SERIAL_NUMBERS"]["TCI_SN_LIST"])  # 访问父类的 CONFIG 属性

# 静态配置：如果配置文件是静态的且不需要频繁更改，使用类属性的方式是合适的
class Father2:
    with open(r"D:\Demo\device_helper\config\device_helper.config", encoding='utf-8') as f:
        CONFIG = json.load(f)
    def __init__(self):
        pass
class Son2(Father2):
    def __init__(self):
        #super().__init__()  # 调用父类的构造函数
        print(self.CONFIG["BOX_SERIAL_NUMBERS"]["TCI_SN_LIST"])  # 访问父类的 CONFIG 属性

class Son3:
    #FATHER = Father3() # 有定义顺序的困扰NameError: name 'Father3' is not defined
    def __init__(self):
        self.FATHER = Father3()
class Father3:
    def __init__(self):
        print("Father3")

# 创建 Son 的实例
son1 = Son1()
son2 = Son2()
son3 = Son3()

