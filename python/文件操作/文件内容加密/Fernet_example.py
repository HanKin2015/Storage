# -*- coding: utf-8 -*-
"""
文 件 名: Fernet_example.py
文件描述: 
作    者: HanKin
创建日期: 2023.12.12
修改日期：2023.12.12

Copyright (c) 2023 HanKin. All rights reserved.
"""
from cryptography.fernet import Fernet

# 生成一个随机的密钥
def generate_key():
    return Fernet.generate_key()

# 用密钥加密文件
def encrypt_file(key, input_file, output_file):
    with open(input_file, 'rb') as f:
        data = f.read()
    fernet = Fernet(key)
    encrypted = fernet.encrypt(data)
    with open(output_file, 'wb') as f:
        f.write(encrypted)

# 用密钥解密文件
def decrypt_file(key, input_file, output_file):
    with open(input_file, 'rb') as f:
        data = f.read()
    fernet = Fernet(key)
    decrypted = fernet.decrypt(data)
    with open(output_file, 'wb') as f:
        f.write(decrypted)

# 生成一个随机的密钥
key = generate_key()

# 加密文件
encrypt_file(key, 'plain.txt', 'encrypted.txt')

# 解密文件
decrypt_file(key, 'encrypted.txt', 'decrypted.txt')

