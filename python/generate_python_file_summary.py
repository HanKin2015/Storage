# -*- coding: utf-8 -*-
"""
文 件 名: generate_python_file_summary.py
文件描述: 自动生成python脚本摘要
备    注: 通过读取文件规范头部信息获取
作    者: HanKin
创建日期: 2023.02.21
修改日期：2023.02.21

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import os

# 当前相对路径
absolute_path = './'
#当前绝对路径
relative_path = os.getcwd()

def get_file_path():
    '''获取文件相对路径
    '''
    file_path = []
    for root,dirs,files in os.walk('.'):
        for file in files:
            #print(root, dirs, file)
            #print(root+'\\'+file)
            #print(file) 
            file_path.append(root+'\\'+file)
    return file_path

def get_file_catalog_name(file_path):
    '''获取文件的目录名称
    '''
    print('正在读取', file_path)
    
    
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            while True:
                line = f.readline() 
                if line:
                    if line[0] == '#':
                        catalog_name = line[2:-1]
                        #print(catalog_name)
                        return catalog_name
                        break
                else:
                    break
    except Exception as ex:
        print('打开文件失败', ex)
        pass
    
def get_type():
    dirs = os.listdir()
    print(dirs)
    
    current_path = os.getcwd()
    print(current_path)
    
    for dir in dirs:
        if os.path.isfile(dir):
            print(dir, "is file")
        elif os.path.isdir(dir):
            print(dir, "is dir")
        else:
            print(dir, "is not file and dir")

# 过滤的文件夹
filter_dirs = ['.', './node_modules', './.git', './Styles', './Source', './_book']

def generate_summary():
    '''生成summary.md目录文件
    '''
    
    count = 0
    summary_file = absolute_path + 'SUMMARY.md'
    with open(summary_file, 'w', encoding = 'utf-8', newline = '\n') as f:
        f.write('# Summary\n\n')
        f.write('* [前言](README.md)\n')
        
        for root, dirs, files in os.walk('.'):
            root = root.replace('\\', '/')
            #print(root)
            if root.count('/') > 1:
                print('this is a multistage directory [{}], filter out'.format(root))
                continue
            if root in filter_dirs:
                print('this is a special filter directory [{}], filter out'.format(root))
                continue
            #print(root)
            # 获取目录文件夹README.md文件目录名称
            root_path = root + '/README.md'
            root_catalog_name = get_file_catalog_name(root_path)
            print(root_path, root_catalog_name)
            
            f.write('* [{}]({})\n'.format(root_catalog_name, root_path))
            count += 1
            for file in files:
                if file == 'README.md':
                    continue
                file_path = root + '/' + file
                file_catalog_name = get_file_catalog_name(file_path)
                #print('\t', file) 
                f.write('    * [{}]({})\n'.format(file_catalog_name, file_path))
                count += 1
        f.write('\n')   # 为了与自动生成SUMMARY.md文件一致
    print('generate summary suceccd，there are {} markdown files'.format(count))

def main():
    """主函数
    """
    
    #file_path = get_file_path()
    #print(file_path)
    #file_catalog_name = get_file_catalog_name('./readme.md')
    #print(file_catalog_name)
    
    generate_summary()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))

