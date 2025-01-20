# -*- coding: utf-8 -*-
"""
文 件 名: solution.py
文件描述: 线程问题解决方案eventlet.spawn
作    者: HanKin
备    注: http://127.0.0.1:5000
创建日期: 2025.01.19
修改日期：2025.01.19

Copyright (c) 2025 HanKin. All rights reserved.
"""
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import eventlet
import time
import threading
import tkinter as tk
from tkinter import messagebox
import json
from show_error_interface import *

# 创建 Flask 应用
app = Flask(__name__)
# 初始化 SocketIO
#socketio = SocketIO(app, async_mode='eventlet')
eventlet.monkey_patch()
socketio = SocketIO(app, cors_allowed_origins='*', async_mode='eventlet')

@app.route('/')
def index():
    return render_template('index.html')  # 你可以创建一个简单的 HTML 文件

def show_error(message):
    """显示错误提示框"""
    # 创建一个新的线程来运行 Tkinter
    def run_tkinter():
        root = tk.Tk()
        root.withdraw()  # 隐藏主窗口
        root.attributes('-topmost', True)   # 设置窗口为置顶
        messagebox.showerror("删除以下映射白名单", message)
        root.destroy()  # 销毁主窗口

    if len(message) == 0:
        logger.info("message length is zero, no error")
        return
    json_strings = [json.dumps(item, ensure_ascii=False) for item in message]
    message = "\n".join(json_strings)
    # 启动 Tkinter 线程
    #threading.Thread(target=run_tkinter).start()
    # 使用 eventlet.spawn 启动 Tkinter 线程
    eventlet.spawn(run_tkinter)

@socketio.on('connect')
def handle_connect():
    print('Client connected')
    # 启动后台任务
    #socketio.start_background_task(target=show_error, message="hejian")
    show_error("hejian")
    print("start background task success")

@socketio.on('disconnect')
def handle_disconnect():
    print('Client disconnected')

if __name__ == '__main__':
    socketio.run(app, debug=False, host='0.0.0.0', port=5000)
