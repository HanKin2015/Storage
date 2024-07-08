# -*- coding: utf-8 -*-
"""
文 件 名: flask_server.py
文件描述: 使用Flask的限流功能，例如flask_limiter扩展，它可以限制用户在一定时间内发出的请求数量
作    者: HanKin
创建日期: 2024.07.05
修改日期：2024.07.05

Copyright (c) 2024 HanKin. All rights reserved.
"""

from flask import Flask, request
from flask import request
from flask import jsonify
import threading
import socket
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address

app = Flask(__name__)
# 配置限速规则，例如限制每个IP每分钟最多访问3次
# 注意一定要写app=app，否则报错https://www.jianshu.com/p/8181817b86bf
limiter = Limiter(app=app, key_func=get_remote_address, default_limits=['3 per minute'])

terminate = False

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

@app.errorhandler(404)
@limiter.limit('3 per minute', error_message="Too Many Requests")  # 设置访问限制，每分钟最多允许10次请求
def handle_404(error):
    """
    捕获客户端访问不存在的接口错误404，即爆破行为
    """
    response = {
        "message": "Not Found",
        "status": 404
    }
    client_ip = request.remote_addr
    print("Client IP:", client_ip)
    print(get_remote_address())
    return jsonify(response), 404

def handle_telnet_request(client_socket):
    while True:
        data = client_socket.recv(1024)
        if not data:
            break
        if data == b'\r\n':
            break
        print(data)
        data = data.decode("latin-1")

        # 在这里进行输入内容的过滤和处理
        filtered_data = filter_input(data)
        print("Filtered input:", filtered_data)
        
def filter_telnet_request():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(("0.0.0.0", 23))
    server_socket.listen(1)

    print("Waiting for telnet connection...")

    while not terminate:
        client_socket, client_address = server_socket.accept()
        print("Telnet connection established from:", client_address)

        try:
            handle_telnet_request(client_socket)
        except KeyboardInterrupt:
            print("Telnet connection terminated by user.")
            break

        client_socket.close()

def filter_input(data):
    # 在这里实现输入内容的过滤逻辑
    # 可以根据需要进行字符串处理、正则表达式匹配等操作
    filtered_data = data.upper()  # 示例：将输入内容转换为大写

    return filtered_data

if __name__ == '__main__':
    t = threading.Thread(target=filter_telnet_request)
    t.start()
    #t.join()
    app.run(host='0.0.0.0', port=8029, debug=False)
    terminate = True