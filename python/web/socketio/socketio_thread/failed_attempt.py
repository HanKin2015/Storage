# -*- coding: utf-8 -*-
"""
文 件 名: failed_attempt.py
文件描述: 线程问题一些失败的尝试
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

# 创建 Flask 应用
app = Flask(__name__)
# 初始化 SocketIO
socketio = SocketIO(app, async_mode='eventlet')

@app.route('/')
def index():
    return render_template('index.html')  # 你可以创建一个简单的 HTML 文件

@socketio.on('message')
def handle_message(data):
    print('Received message: ' + data)
    # 发送响应
    emit('response', {'data': 'Message received!'})

def background_task():
    """后台任务示例"""
    while True:
        socketio.sleep(10)  # 每10秒执行一次
        socketio.emit('background_event', {'data': 'This is a background event!'})
        current_time = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
        print("{}: browser console receives message".format(current_time))

class Test:
    @staticmethod
    def show_error(message):
        """显示错误提示框"""
        if len(message) == 0:
            return
        json_strings = [json.dumps(item, ensure_ascii=False) for item in message]
        message = "\n".join(json_strings)
        
        # 创建一个隐藏的主窗口
        print("********** show_error **********")
        root = tk.Tk()
        root.withdraw()  # 隐藏主窗口

        # 设置窗口为置顶
        root.attributes('-topmost', True)

        # 弹出错误提示框
        messagebox.showerror("删除以下映射白名单", message)
        print(message)

        # 销毁主窗口
        root.destroy()

    @classmethod
    def check_white_list_valid(cls):
        """后台任务示例"""
        print("check_white_list_valid start")
        invalid_list = [{"device_id": "1234:3212", "cause": "获取客户端信息获取客户端信息"}, {"device_id": "1234:3212", "cause": "获取客户端信息"}, {"device_id": "1234:3212", "cause": "1111"}]
        thread = threading.Thread(target=cls.show_error, args=(invalid_list,))
        thread.daemon = True
        thread.start()
        #socketio.start_background_task(target=cls.show_error, message=invalid_list)
        print("check_white_list_valid end")

def show_error(message):
    """显示错误提示框"""
    root = tk.Tk()
    root.withdraw()  # 隐藏主窗口
    root.attributes('-topmost', True)   # 设置窗口为置顶
    messagebox.showerror("删除以下映射白名单", message)
    print(message)
    root.destroy()  # 销毁主窗口

@socketio.on('connect')
def handle_connect():
    print('Client connected')
    
    # start_background_task函数启动后台任务
    #socketio.start_background_task(target=background_task)
    socketio.start_background_task(target=Test.show_error, message="hejian")
    
    # 类调用启动后台任务
    #Test.check_white_list_valid()
    
    # 文件调用启动该后台任务
    #BlueprintInterface().check_white_list_valid()
    print("start background task success")

@socketio.on('disconnect')
def handle_disconnect():
    print('Client disconnected')

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)
