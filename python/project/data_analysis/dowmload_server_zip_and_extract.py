# -*- coding: utf-8 -*-
"""
文 件 名: dowmload_server_zip_and_extract.py
文件描述: 下载zip包并解压缩
备    注: 
作    者: HanKin
创建日期: 2024.01.05
修改日期：2024.01.05

Copyright (c) 2024 HanKin. All rights reserved.
"""
import requests
import os
import datetime
from contextlib import closing
import zipfile
import shutil

if __name__ == '__main__':
    basedir = os.path.abspath(os.path.dirname(__file__))
    print(basedir)
    folder_date = (datetime.datetime.now() - datetime.timedelta(days=1)).strftime("%Y%m%d")
    print(folder_date)
    report_url = "http://12.12.14.246:8852/FTP%E6%9C%8D%E5%8A%A1%E5%99%A8/USB%E5%B7%A5%E5%85%B7/USBTrace_Installer.zip"
    
    if not os.path.exists('tmp'):
        os.makedirs('tmp')
    else:
        if os.path.isdir('tmp'):
            shutil.rmtree('tmp', ignore_errors=True)
        os.makedirs('tmp')
    
    tmp_path = os.path.join(basedir, 'tmp/{}.zip'.format(folder_date))
    print(tmp_path)
    
    with closing(requests.get(report_url, stream=True)) as response:
        chunk_size = 1024  # 单次请求最大值
        # response.headers['content-length']得到的数据类型是str而不是int
        content_size = int(response.headers['content-length'])  # 文件总大小
        print(content_size)
        data_count = 0  # 当前已传输的大小
        with open(tmp_path, "wb") as file:
            for data in response.iter_content(chunk_size=chunk_size):
                file.write(data)
                done_block = int((data_count / content_size) * 50)
                # 已经下载的文件大小
                data_count = data_count + len(data)
                # 实时进度条进度
                now_jd = (data_count / content_size) * 100
                # %% 表示%
                print("\r [%s%s] %d%% " % (done_block * '█', ' ' * (50 - 1 - done_block), now_jd), end=" ")
 
    file = zipfile.ZipFile(tmp_path)
    file.extractall(os.path.join(basedir, 'tmp'))
    file.close()

    
 