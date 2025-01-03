# -*- coding: utf-8 -*-
"""
文 件 名: server.py
文件描述: 服务端收文件（收日志和dump文件）
作    者: HanKin
创建日期: 2025.01.02
修改日期：2025.01.02

Copyright (c) 2025 HanKin. All rights reserved.
"""
from flask import Flask, request, redirect, url_for, send_from_directory
import os

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        if 'file' not in request.files:
            return 'No file part'
        file = request.files['file']
        if file.filename == '':
            return 'No selected file'
        if file:
            file.save(os.path.join(UPLOAD_FOLDER, file.filename))
            return 'File uploaded successfully'
    return '''
    <!doctype html>
    <title>Upload File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(UPLOAD_FOLDER, filename)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8852)
