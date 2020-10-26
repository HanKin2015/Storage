# -*- coding: utf-8 -*-
"""
Created on Mon Aug  3 14:17:24 2020

@author: hankin
@description:
    gitbook的SUMMARY.md自动生成脚本
    规定md文件读取第一个#开头的句子作为子目录名
"""

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
        with open(file_path, 'r') as f:
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
    except:
        print('打开文件失败')
    
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

def generate_summary():
    '''生成summary.md目录文件
    '''
    summary_file = absolute_path + 'SUMMARY.md'
    
    
    with open(summary_file, 'w') as f:
        f.write('# Summary\n\n')
        f.write('* [前言](README.md)\n')
        
        for root, dirs, files in os.walk('.'):
            print(root)
            if root == '.':
                continue
            #print(root)
            # 获取目录文件夹README.md文件目录名称
            root_path = root + '\\README.md'
            root_catalog_name = get_file_catalog_name(root_path)
            #print(root_catalog_name)
            
            f.write('* [{}]({})\n'.format(root_catalog_name, root_path))
            for file in files:
                file_path = root + '\\' + file
                file_catalog_name = get_file_catalog_name(file_path)
                #print('\t', file) 
                f.write('\t* [{}]({})\n'.format(file_catalog_name, file_path))
        
    print('generate summary suceccd')

  


def main():
    file_path = get_file_path()
    print(file_path)
    file_catalog_name = get_file_catalog_name('./Blog/hj.txt')
    print(file_catalog_name)
    
    generate_summary()
    print('done')

if __name__=='__main__':
    main()
    
    for root, dirs, files in os.walk('./'):
        print(root)
        for file in files:
            print('\t', file)
        #break
    
    


