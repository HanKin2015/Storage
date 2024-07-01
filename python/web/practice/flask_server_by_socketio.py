# -*- coding: utf-8 -*-
"""
文 件 名: flask_server_by_socketio.py
文件描述: 使用socketio进行长连接（这个文件不可行，见D:\Github\Storage\python\web\socketio\example）
备    注: pip install flask_socketio
作    者: HanKin
创建日期: 2024.07.01
修改日期：2024.07.01

Copyright (c) 2024 HanKin. All rights reserved.
"""

from flask import Flask
from flask import request
from flask import jsonify
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app)

@socketio.on('hello_long_connection')
def hello_long_connection():
    return 'Hello, long connection!'

@app.route('/hello_short_connection')
def hello_short_connection():
    return 'Hello, short connection!'

@app.route('/hello_world', methods=['GET'])
def hello_world():
    # get请求及参数获取方式
    # 获取参数对应值
    name = request.args.get("name")
    return "welcome" + " " + name

@app.route('/hello_check', methods=['POST'])
def hello_check():
    # post请求及参数获取方式
    # 获取参数对应值
    name = request.form.get("name")
    return "welcome" + " " + name

@app.route('/hello_sync', methods=['POST'])
def hello_sync():
    # post请求及参数获取方式
    # 获取参数对应值
    data = request.get_json()
    name = data['name']
    code = data['code']
    # return "welcome" + " " + name + " " + code
    return jsonify({"login": name, "token": 9})

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=8029, debug=False)