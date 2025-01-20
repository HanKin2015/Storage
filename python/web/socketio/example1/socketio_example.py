# -*- coding: utf-8 -*-
"""
文 件 名: socketio_example.py
文件描述: socketio库示例
作    者: HanKin
备    注: http://127.0.0.1:8029/
创建日期: 2025.01.19
修改日期：2025.01.19

Copyright (c) 2025 HanKin. All rights reserved.
"""
from flask import Flask, request,render_template
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app)

@app.route('/')
def hello_world():  # put application's code here
    return render_template("index.html")

@socketio.on('connect')
def connect():
    print('ip:' + request.remote_addr)
    print('sid:' + request.sid)

@socketio.on('send_success')
def send_success_event(data):
    print(data)
    return {"result": "success"}

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=8029, debug=False)

