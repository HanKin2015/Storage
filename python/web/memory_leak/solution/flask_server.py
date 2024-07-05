# -*- coding: utf-8 -*-
"""
文 件 名: flask_server.py
文件描述: 使用Flask的限流功能，例如flask_limiter扩展，它可以限制用户在一定时间内发出的请求数量
作    者: HanKin
创建日期: 2024.07.05
修改日期：2024.07.05

Copyright (c) 2024 HanKin. All rights reserved.
"""

from flask import Flask
from flask import request
from flask import jsonify
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address

app = Flask(__name__)
# 配置限速规则，例如限制每个IP每分钟最多访问3次
# 注意一定要写app=app，否则报错https://www.jianshu.com/p/8181817b86bf
limiter = Limiter(app=app, key_func=get_remote_address, default_limits=['3 per minute'])

@app.route('/hello_flask', methods=['POST'])
@limiter.limit('2 per minute')  # 限制每个IP每分钟最多访问2次
def hello_flask():
    """
    这个接口在客户端访问第3次的时候报错
    <!doctype html>
    <html lang=en>
    <title>429 Too Many Requests</title>
    <h1>Too Many Requests</h1>
    <p>2 per 1 minute</p>
    """
    return 'Hello, World!'

@app.route('/hello_world', methods=['GET'])
def hello_world():
    """
    get请求及参数获取方式
    获取参数对应值
    
    这个接口在客户端访问第4次的时候报错
    <!doctype html>
    <html lang=en>
    <title>429 Too Many Requests</title>
    <h1>Too Many Requests</h1>
    <p>3 per 1 minute</p>
    """

    name = request.args.get("name")
    return "welcome" + " " + name

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8029, debug=False)