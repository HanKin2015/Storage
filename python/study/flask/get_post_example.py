# -*- coding: utf-8 -*-
"""
文 件 名: get_post_example.py
文件描述: flask框架学习
作    者: HanKin
创建日期: 2023.09.07
修改日期：2023.09.07

Copyright (c) 2023 HanKin. All rights reserved.
"""

from flask import Flask
from flask import request
from flask import jsonify

app = Flask(__name__)

@app.route('/')
def hello_flask():
    return 'Hello, World!'

@app.route('/login', methods=['GET'])
def hello_world():
    # get请求及参数获取方式
    # 获取参数对应值
    name = request.args.get("name")
    return "welcome" + " " + name

@app.route('/check', methods=['POST'])
def hello_check():
    # post请求及参数获取方式
    # 获取参数对应值
    name = request.form.get("name")
    return "welcome" + " " + name

@app.route('/sync', methods=['POST'])
def hello_sync():
    # post请求及参数获取方式
    # 获取参数对应值
    data = request.get_json()
    name = data['name']
    code = data['code']
    # return "welcome" + " " + name + " " + code
    return jsonify({"login": name, "token": 9})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8029, debug=False)