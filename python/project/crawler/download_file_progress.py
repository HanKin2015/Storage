# -*- coding: utf-8 -*-
"""
文 件 名: download_file_progress.py
文件描述: 下载文件显示进度条
备    注: https://blog.csdn.net/knighthood2001/article/details/120624571
作    者: HanKin
创建日期: 2024.01.04
修改日期：2024.01.04

Copyright (c) 2024 HanKin. All rights reserved.
"""
from contextlib import closing
from requests import get
url = 'https://tb-video.bdstatic.com/tieba-smallvideo-transcode-crf/2161259_a1e6a853846c3dbb5c883f5877997dea_d4b74c9f1c18_0.mp4?vt=1&pt=3&ver=&cr=2&cd=0&sid=&ft=8&tbau=2024-01-05_960932ff88e513867918e3d57beca14b55e007aeca078a813bfd4f6e2a4052fa&ptid=8667781861'
 
with closing(get(url, stream=True)) as response:
    chunk_size = 1024  # 单次请求最大值
    # response.headers['content-length']得到的数据类型是str而不是int
    content_size = int(response.headers['content-length'])  # 文件总大小
    data_count = 0  # 当前已传输的大小
    with open('文件名.mp4', "wb") as file:
        for data in response.iter_content(chunk_size=chunk_size):
            file.write(data)
            done_block = int((data_count / content_size) * 50)
            # 已经下载的文件大小
            data_count = data_count + len(data)
            # 实时进度条进度
            now_jd = (data_count / content_size) * 100
            # %% 表示%
            print("\r [%s%s] %d%% " % (done_block * '█', ' ' * (50 - 1 - done_block), now_jd), end=" ")