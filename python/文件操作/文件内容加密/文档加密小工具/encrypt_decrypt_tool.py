# -*- coding: utf-8 -*-
"""
文 件 名: encrypt_decrypt_tool.py
文件描述: 加密解密工具
作    者: HanKin
创建日期: 2024.01.02
修改日期：2025.01.20

Copyright (c) 2024 HanKin. All rights reserved.
"""
import base64
import sys

def encrypt_file(input_file, output_file, shift):
    """
    使用base64库加密文件并右移x位
    :param input_file: 输入文件
    :param output_file: 输出文件
    :param shift: 右移位数
    :return null: 无
    """
    with open(input_file, 'r', encoding='utf-8') as file:
        data = file.read()
    # 将中文内容转换为字节流
    data_bytes = data.encode('utf-8')
    source = base64.b64encode(data_bytes).decode()
    # 对字符串加密 右移x位(致富密码最后一位数)
    result = ''
    for i in source:
        if ord(i) in range(97, 123) or ord(i) in range(65, 91):
            result += chr(ord(i)+shift)
        else:
            result += i
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(result)
    print("encrypt file success, output file path: {}".format(output_file))

def decrypt_file(input_file, output_file, shift):
    """
    使用base64库解密文件并左移x位
    :param input_file: 输入文件
    :param output_file: 输出文件
    :param shift: 左移位数
    :return null: 无
    """
    with open(input_file, 'r', encoding='utf-8') as file:
        data = file.read()
    result = ''
    for i in data:
        if ord(i) in range(97+shift, 123+shift) or ord(i) in range(65+shift, 91+shift):
            result += chr(ord(i) - shift)
        else:
            result += i
 
    result = base64.b64decode(result)
    # 将字节流转换为str中文内容
    result_str = result.decode('utf-8')
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(result_str)
    print("decrypt file success, output file path: {}".format(output_file))

if __name__ == '__main__':
    argv_cnt = len(sys.argv)
    if argv_cnt < 3:   # 脚本名 加解密操作 输入文件 输出文件(非必须)
        print('argument count is less than two, need opt(e or d) and input file path or ouput file path')
        sys.exit()
    opt = sys.argv[1]
    input_file = sys.argv[2]
    output_file = 'output_file.md'
    if argv_cnt == 4:
        output_file = sys.argv[3]
    shift = 8   # 致富密码最后一位数
    if opt == 'e':
        encrypt_file(input_file, output_file, shift)
    elif opt == 'd':
        decrypt_file(input_file, output_file, shift)
    else:
        print("option is unknow!")
