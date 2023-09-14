# -*- coding: utf-8 -*-
"""
文 件 名: flask_example.py
文件描述: flask框架学习
作    者: HanKin
创建日期: 2023.09.04
修改日期：2023.09.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

# 从 Flask 这个包中导入 flask 这个类
from flask import Flask

# 使用Flask类创建一个app对象
# __name__ 代表当前的这个模块
# 1.以后出现bug，它可以帮助我们快速定位
# 2.对于寻找模板文件，有一个相对路径
app = Flask(__name__)

# 创建一个路由和视图函数的映射
# 创建的是根路由
# 访问根路由，就会执行hello_world这个函数
@app.route('/')
def hello_world():  # put application's code here
    return 'Hello World!'

# 运行代码
if __name__ == '__main__':
    app.run()