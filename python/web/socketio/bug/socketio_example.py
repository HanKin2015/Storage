# -*- coding: utf-8 -*-
"""
文 件 名: socketio _example.py
文件描述: 学习SocketIO
备    注: pip install flask_socketio
作    者: HanKin
创建日期: 2023.09.22
修改日期：2023.09.22

Copyright (c) 2023 HanKin. All rights reserved.
"""

from flask import Flask, render_template
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

@socketio.on('my event')
def handle_my_custom_event(json):
    print('received json: ' + str(json))
    socketio.emit('my response', json)

if __name__ == '__main__':
    socketio.run(app)
