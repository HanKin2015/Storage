# -*- coding: utf-8 -*-
"""
文 件 名: upload_and_download_server.py
文件描述: 服务端代码-上传和下载、保活
作    者: HanKin
创建日期: 2024.10.11
修改日期：2024.10.11

Copyright (c) 2024 HanKin. All rights reserved.
"""
from flask import Flask, request, send_file, abort
import zipfile
import io
import os
from werkzeug.utils import secure_filename

app = Flask(__name__)

@app.route("/")
def hello():
    return "hello 8002!"

@app.route("/download-folder/<path:foldername>")
def download_folder(foldername):
    folder_path = os.path.join(app.root_path, 'download_files')

    if not os.path.isdir(folder_path):
        abort(404, description="Resource not found")

    memory_file = io.BytesIO()
    with zipfile.ZipFile(memory_file, 'w', zipfile.ZIP_DEFLATED) as zf:
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                file_path = os.path.join(root, file)
                arcname = os.path.relpath(file_path, folder_path)
                zf.write(file_path, arcname)
    
    memory_file.seek(0)
    return send_file(memory_file, mimetype='application/zip', as_attachment=True, attachment_filename=f"{foldername}.zip")

@app.route('/upload_file', methods=['POST'])
def upload_file():
    file_dir = 'upload_files'
    if not os.path.exists(file_dir):
        os.makedirs(file_dir)

    file = request.files['file']
    if file:
        filename = secure_filename(file.filename)
        file.save(os.path.join(file_dir, filename))
        return 'success'
    else:
        return 'fail, no file'

if __name__ == '__main__':
    app.run(debug=False, port=8002, host="0.0.0.0")