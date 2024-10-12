# -*- coding: utf-8 -*-
"""
文 件 名: upload_and_download_client.py
文件描述: 客户端代码-上传和下载、保活
备    注: 
作    者: HanKin
创建日期: 2024.10.11
修改日期：2024.10.11

Copyright (c) 2024 HanKin. All rights reserved.
"""
import json
import requests
import time
import os
import sys

def upload_files():
    """向服务端上传多个文件
    """
    
    files_path = 'upload_files/'
    try:
        for filename in os.listdir(files_path):
            print('filename: {}'.format(filename))
            f = open(files_path + filename, 'rb')
            file = {"file": (filename, f)}
            res = requests.post(url='http://121.46.130.154:8002/upload_file', files=file, timeout=1)
            if res.text:
                print(res.text)
    except Exception as err:
        # failed, ('Connection aborted.', TimeoutError(10060, '由于连接方在一段时间后没有正确答复或连接的主机没有反应，连接尝试失败。', None, 10060, None)
        print('failed, {}'.format(err))
        return False

def download_files():
    """从服务端下载多个文件
    """
    
    # 发送 HTTP GET 请求（请求的内容会以流的方式下载，这样可以逐块处理响应体，适合下载大文件）
    with requests.get('http://121.46.130.154:8002/download-folder/download_files', stream=True) as response:
        # 检查请求是否成功（状态码为 200）。如果请求失败（例如 404 或 500 错误），会抛出一个异常
        response.raise_for_status()
        # 打开本地文件以写入二进制数据
        with open('download_files.zip', 'wb') as file:
            # 分块写入文件（每次读取 8192 字节（8 KB））
            for chunk in response.iter_content(chunk_size=8192):
                file.write(chunk)
    print('download files success')
    
if __name__ == '__main__':
    argv_cnt = len(sys.argv)
    if argv_cnt == 2:
        print('download files')
        download_files()
        sys.exit()  # 使用 sys.exit() 退出程序
    print('upload files')
    upload_files()