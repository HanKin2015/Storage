# -*- coding: utf-8 -*-
"""
文 件 名: AES_example.py
文件描述: 使用AES算法进行加密和解密
作    者: HanKin
创建日期: 2023.12.08
修改日期：2023.12.08

Copyright (c) 2023 HanKin. All rights reserved.
"""
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.backends import default_backend
import os

# 加密文件
def encrypt_file(input_file, output_file):
    with open(input_file, 'rb') as f:
        data = f.read()

    # 生成随机的128位密钥和初始向量
    key = os.urandom(16)
    iv = os.urandom(16)

    # 初始化AES加密器和解密器
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    encryptor = cipher.encryptor()

    # 使用PKCS7填充
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(data) + padder.finalize()

    # 加密数据
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()

    # 将密钥、初始向量和加密后的数据写入输出文件
    with open(output_file, 'wb') as f:
        f.write(key)
        f.write(iv)
        f.write(encrypted_data)

# 解密文件
def decrypt_file(input_file, output_file):
    with open(input_file, 'rb') as f:
        key = f.read(16)
        iv = f.read(16)
        encrypted_data = f.read()

    # 初始化解密器
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()

    # 解密数据
    decrypted_data = decryptor.update(encrypted_data) + decryptor.finalize()

    # 使用PKCS7填充解密后的数据
    unpadder = padding.PKCS7(128).unpadder()
    unpadded_data = unpadder.update(decrypted_data) + unpadder.finalize()

    # 将解密后的数据写入输出文件
    with open(output_file, 'wb') as f:
        f.write(unpadded_data)

if __name__ == '__main__':
    # 使用示例
    encrypt_file('p.py', 'encrypted.bin')
    decrypt_file('encrypted.bin', 'p.txt')
