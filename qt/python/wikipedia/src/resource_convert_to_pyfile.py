# -*- coding: utf-8 -*-
"""
文 件 名: resource_convert_to_pyfile.py
文件描述: 把图片文件转换成py文件保存，并读取文件版本信息
备    注: 图片使用时需要base64.b64decode(udev_detect_ico)转换
作    者: HanKin
创建日期: 2023.02.27
修改日期：2023.03.13

Copyright (c) 2023 HanKin. All rights reserved.
"""


import base64
import time
import os
from PIL import Image

def convert_png_to_ico(dir_path, size_list=None):
    """把png转换为ico图标
    """
    
    # 获取目录下文件名
    file_names = os.listdir(dir_path)
    
    # 图标大小
    default_size_list = [
        (40, 40) # 默认生成ico大小
    ]
    size_list = size_list or default_size_list

    # 给图标文件单独创建一个icon目录
    #if not os.path.exists('icon'):
    #    os.mkdir('icon')

    for file_name in file_names:
        # 分离文件名与扩展名
        tmp = os.path.splitext(file_name)
        
        # 因为存在ico、jpeg、png在同目录，所以需要判断一下
        if tmp[1] == '.png':
            new_file_name = tmp[0] + '.ico'
            # 打开图片并设置大小
            file_path = '{}\{}'.format(dir_path, file_name)
            new_file_path = '{}\{}'.format(dir_path, new_file_name)
            im = Image.open(file_path).resize(size_list[0])
            try:
                # 图标文件保存至icon目录
                path = os.path.join(dir_path, new_file_path)
                im.save(path, sizes=size_list)

                print('{} --> {}'.format(file_name, new_file_name))
            except IOError:
                print('connot convert :', file_name)

def image_convert_to_pyfile(dir_path, pyfile_path):
    """将图片转换成base64编码
    """
    
    # 获取目录下文件名
    file_names = os.listdir(dir_path)
    
    for file_name in file_names:
        file_path = '{}\{}'.format(dir_path, file_name)
        with open(file_path, 'rb') as img:
            img_str = base64.b64encode(img.read())
        
            # 分离文件名与扩展名
            tmp = os.path.splitext(file_name)
            suffix = tmp[1][1:]
            img_format = '{}_{} = {}'.format(tmp[0], suffix, str(img_str))

            with open(pyfile_path, 'a+', encoding='utf8') as fd:
                fd.write(img_format)
                fd.write('\n')

def find_info_value(line, key, pyfile_path):
    """查找相关信息
    """
    
    if key in line:
        #print(line)
        start_index = line.rfind('u\'')
        end_index   = line.rfind('\'')
        value = line[start_index+2:end_index]
        print(value)
        with open(pyfile_path, 'a+', encoding='utf8') as fd:
            var_format = '{} = \'{}\''.format(key, value)
            fd.write(var_format)
            fd.write('\n')

def file_version_info_to_pyfile(file_version_info_path, pyfile_path):
    """读取file_version_info.txt文件
    """
    
    with open(file_version_info_path, 'r', encoding='utf8') as file_version_info:
        for line in file_version_info.readlines():
            find_info_value(line, 'FileDescription', pyfile_path)
            find_info_value(line, 'InternalName', pyfile_path)
            find_info_value(line, 'LegalCopyright', pyfile_path)
            find_info_value(line, 'ProductVersion', pyfile_path)

def main():
    """主函数
    """
    
    pyfile_path = './resource.py'
    dir_path = r'../img'
    file_version_info_path = '../doc/file_version_info.txt'
    
    if not os.path.exists(dir_path):
        #print('image path not exist')
        return
    
    # 因为需要追写文件，所以写之前需要删除
    if os.path.exists(pyfile_path):
        os.remove(pyfile_path)
    
    # 转换图片
    convert_png_to_ico(dir_path)
    image_convert_to_pyfile(dir_path, pyfile_path)
    
    # 读取文件信息
    file_version_info_to_pyfile(file_version_info_path, pyfile_path)

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))