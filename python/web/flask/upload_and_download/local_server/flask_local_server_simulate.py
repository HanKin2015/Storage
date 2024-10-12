# -*- coding: utf-8 -*-
"""
文 件 名: flask_local_server_simulate
文件描述: 本地模拟远端服务器接口进行测试
作    者: HanKin
创建日期: 2024.04.03
修改日期：2024.10.09

Copyright (c) 2024 HanKin. All rights reserved.
"""
from flask import Flask
from flask import request
from flask import send_from_directory
from flask import send_file, abort
import zipfile
import io
import datetime
import os
from werkzeug.utils import secure_filename
from threading import Lock

app = Flask(__name__)

UPLOAD_FOLDER = ''
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
basedir = os.path.abspath(os.path.dirname(__file__))
# 文件允许通过的类型列表
ALLOWED_EXTENSIONS = set(['zip', '7z', 'xls', 'xlsx', 'csv', 'docx', 'txt'])
file_lock = Lock()

# 服务是否启动测试接口
#（强烈建议写这个函数，不然的话直接打开默认网址会报错Not Found，以为服务启动失败，实际失败则报错无法访问此网站。
# 因此也好理解了为何这里最好是加载html文件，使用render_template函数）
@app.route("/")
def hello():
    return "hello!"

# 文件类型校验函数
def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

# 下载文件（<path:filename>：这是一个动态部分，表示 URL 中的这一部分可以是任意值，并且会被传递给视图函数作为参数。path 转换器允许斜杠 / 出现在参数中，这意味着它可以匹配多级路径（例如，subdir/file.txt））
@app.route("/download/<path:filename>")
def downloader(filename):
    # 定义文件存储的目录
    dirpath = os.path.join(app.root_path, 'download')
    
    # 使用 send_from_directory 发送文件
    return send_from_directory(dirpath, filename, as_attachment=True)

# Flask 本身并不直接支持下载整个文件夹，因为 HTTP 协议通常用于传输单个文件
@app.route("/download-folder/<path:foldername>")
def download_folder(foldername):
    # 定义文件夹的路径
    folder_path = os.path.join(app.root_path, 'download', foldername)
    
    # 检查文件夹是否存在
    if not os.path.isdir(folder_path):
        abort(404, description="Resource not found")

    # 创建一个内存中的字节流
    memory_file = io.BytesIO()
    
    # 创建一个 ZIP 文件
    with zipfile.ZipFile(memory_file, 'w', zipfile.ZIP_DEFLATED) as zf:
        # 遍历文件夹中的所有文件
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                # 计算文件的完整路径
                file_path = os.path.join(root, file)
                # 计算文件在 ZIP 文件中的相对路径
                arcname = os.path.relpath(file_path, folder_path)
                # 将文件写入 ZIP 文件
                zf.write(file_path, arcname)
    
    # 将指针移到字节流的开头
    memory_file.seek(0)
    
    # 发送 ZIP 文件
    return send_file(memory_file, mimetype='application/zip', as_attachment=True, download_name=f"{foldername}.zip")

# 上传文件（接收来自客户端的文件）
@app.route('/upload_file', methods=['POST'])
def upload_file():
    today = datetime.date.today().strftime("%Y%m%d")
    print('today: {}'.format(today))
    file_dir = os.path.join(basedir, app.config['UPLOAD_FOLDER']) + '//device_data//' + today
    isExists = os.path.exists(file_dir)
    if not isExists:
        os.makedirs(file_dir)
    else:
        pass
    file = request.files['file']
    # 判断是否是允许上传的文件类型
    if file:
        if allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(file_dir, filename))
            return 'success'
        else:
            return 'fail, file type is not in {}'.format(ALLOWED_EXTENSIONS)
    else:
        return 'fail, no file'

# 运行代码
if __name__ == '__main__':
    app.run(debug=False, port=8001, host="0.0.0.0")