# -*- coding: utf-8 -*-
"""
文 件 名: AES_encrypt_decrypt.py
文件描述: AES算法加解密
作    者: HanKin
创建日期: 2024.03.29
修改日期：2024.03.29

Copyright (c) 2024 HanKin. All rights reserved.
"""

from common import *
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding
from cryptography.hazmat.backends import default_backend

def encrypt_data(data):
    """
    使用AES算法加密数据
    :param data: 原始数据
    :return encrypted_data: 加密后的数据
    """

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

    # 将密钥、初始向量和加密后的数据返回
    return key, iv, encrypted_data

def decrypt_data(encrypted_data):
    """
    使用AES算法解密数据
    :param encrypted_data: 加密后的数据
    :return unpadded_data: 解密后的数据
    """

    # 初始化解密器
    cipher = Cipher(algorithms.AES(key), modes.CBC(iv), backend=default_backend())
    decryptor = cipher.decryptor()

    # 解密数据
    decrypted_data = decryptor.update(encrypted_data) + decryptor.finalize()

    # 使用PKCS7填充解密后的数据
    unpadder = padding.PKCS7(128).unpadder()
    unpadded_data = unpadder.update(decrypted_data) + unpadder.finalize()

    # 将解密后的数据返回
    return unpadded_data

def encrypt_file(input_file, output_file):
    """
    使用AES算法加密文件
    :param input_file: 输入文件
    :param output_file: 输出文件
    :return null: 无
    """
    with open(input_file, 'rb') as f:
        data = f.read()

    key, iv, encrypted_data = encrypt_data(data)

    # 将密钥、初始向量和加密后的数据写入输出文件
    with open(output_file, 'wb') as f:
        f.write(key)
        f.write(iv)
        f.write(encrypted_data)

def decrypt_file(input_file, output_file):
    """
    使用AES算法解密文件
    :param input_file: 输入文件
    :param output_file: 输出文件
    :return null: 无
    """
    with open(input_file, 'rb') as f:
        key = f.read(16)
        iv = f.read(16)
        encrypted_data = f.read()

    unpadded_data = decrypt_data(encrypted_data)

    # 将解密后的数据写入输出文件
    with open(output_file, 'wb') as f:
        f.write(unpadded_data)
