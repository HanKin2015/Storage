# -*- coding: utf-8 -*-
"""
文 件 名: flask_server_get_client_real_ip.py
文件描述: 测试服务端获取客户端的真实ip地址
作    者: HanKin
创建日期: 2024.04.03
修改日期：2024.04.03

Copyright (c) 2024 HanKin. All rights reserved.
"""

# 从 Flask 这个包中导入 flask 这个类
from flask import Flask
from flask import request
#from werkzeug.middleware.proxy_fix import ProxyFix

# 使用Flask类创建一个app对象
# __name__ 代表当前的这个模块
# 1.以后出现bug，它可以帮助我们快速定位
# 2.对于寻找模板文件，有一个相对路径
app = Flask(__name__)
#app.wsgi_app = ProxyFix(app.wsgi_app, x_for=1, x_proto=1, x_host=1, x_port=1)

# 创建一个路由和视图函数的映射
# 创建的是根路由
# 访问根路由，就会执行hello_world这个函数
@app.route('/')
def hello_world():  # put application's code here
    return 'Hello World!'

@app.route('/hello_server')
def hello_server():
    return 'Hello server!'

@app.route('/hello_ip', methods=['POST'])
def hello_ip():
    client_ip = request.remote_addr
    print(client_ip)
    file_path = './client_ip.txt'
    with open(file_path, "a", encoding="utf-8") as f:
        f.write('{}\n'.format(client_ip))
    return client_ip

@app.route('/hello_real_ip', methods=['POST'])
def hello_real_ip():
    print(request.headers)
    # 优先从X-Forwarded-For头部获取IP地址
    if 'X-Forwarded-For' in request.headers:
        client_ip = request.headers['X-Forwarded-For'].split(',')[0].strip()
    else:
        print('get real ip from remote_addr')
        client_ip = request.remote_addr
    print(client_ip)
    file_path = './client_ip.txt'
    with open(file_path, "a", encoding="utf-8") as f:
        f.write('{}\n'.format(client_ip))
    return '客户端IP地址是：' + client_ip

@app.route('/get_client_ip', methods=['GET'])
def get_client_ip():
    client_ip = request.remote_addr
    response = {'ip': client_ip}
    return jsonify(response)

# 运行代码
if __name__ == '__main__':
    app.run(debug=False, port=443, host="0.0.0.0")