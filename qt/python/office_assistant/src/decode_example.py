# -*- coding: utf-8 -*-
"""
文 件 名: decode_example.py
文件描述: 用于将字节数据转换成字符串的函数
备    注：https://blog.csdn.net/wangyuxiang946/article/details/131517892
作    者: HanKin
创建日期: 2024.05.23
修改日期：2024.05.23

Copyright (c) 2024 HanKin. All rights reserved.
"""
import time

def decode_example(b):
    """
    bytes_object.decode(encoding='utf-8', errors='strict')
    errors参数可用于指定在转换过程中遇到非法字节时的处理方式，常用的取值有'strict'、'ignore'和'replace'等
    """
    
    s = b.decode()  # 默认编码格式utf-8
    #s = b.decode('utf-8')
    print(s)

def encode_example(s):
    """
    string.encode( encoding, errors )
    encodeing ：（可选）指定编码，默认 UTF-8
    errors ：（可选）设置错误处理方式，默认
    """
    
    b = s.encode()
    print(b)

def main():
    """主函数
    """
    
    decode_example(b'fds\xe6\x88\x9112')
    decode_example(b'\xe8\xad\x8f\xef\xbd\xaf')
    
    encode_example('是')
    encode_example('fds我12')

def debug():
    """调试
    """

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()
    #debug()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))



b'\xe8\xad\x8f\xef\xbd\xaf'