# -*- coding: utf-8 -*-
"""
文 件 名: files_classify.py
文件描述: 按文件后缀对文件进行分类
备    注: 
作    者: HanKin
创建日期: 2021.01.07
修改日期：2023.12.05

Copyright (c) 2023 HanKin. All rights reserved.
"""
import os
import shutil

directory_path = 'D:/Users/Administrator/My Document/WeChat Files/wxid_2gh9d5knc6th21/FileStorage/File/'
filenames = os.listdir(directory_path)  # 列出当前文件夹的所有文件

# 循环遍历每个文件
for filename in filenames:
    print(filename)
    if os.path.isfile(os.path.join(directory_path, filename)):
        # 以扩展名为名称的子文件夹
        file_extension = directory_path + filename.split(".")[-1]
        print(file_extension)
        destination_directory = os.path.join(directory_path, file_extension)
        # 如果不存在该目录，先创建，再移动文件
        if not os.path.exists(destination_directory):
            os.makedirs(destination_directory)

        # 举例：这里的f为 1.png 等同于 ./1.png (因为是相对路径)
        shutil.move(os.path.join(directory_path, filename),
                     os.path.join(destination_directory, filename)
