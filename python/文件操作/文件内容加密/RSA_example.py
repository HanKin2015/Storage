# -*- coding: utf-8 -*-
"""
文 件 名: RSA_example.py
文件描述: RSA算法通常用于加密对称密钥，而不是直接加密文件内容。这是因为RSA算法相对较慢，特别是对于大型文件。一种常见的做法是使用RSA算法来加密对称密钥，然后使用对称密钥来加密和解密文件内容。
作    者: HanKin
创建日期: 2023.12.12
修改日期：2023.12.12

Copyright (c) 2023 HanKin. All rights reserved.
"""
from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives import padding as sym_padding
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

# 生成RSA密钥对
private_key = rsa.generate_private_key(
    public_exponent=65537,
    key_size=2048,
    backend=default_backend()
)
public_key = private_key.public_key()

# 保存RSA密钥对到文件
with open('private_key.pem', 'wb') as f:
    f.write(private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.TraditionalOpenSSL,
        encryption_algorithm=serialization.NoEncryption()
    ))

with open('public_key.pem', 'wb') as f:
    f.write(public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    ))

# 加密文件
def encrypt_file(public_key_file, input_file, output_file):
    with open(public_key_file, 'rb') as f:
        public_key = serialization.load_pem_public_key(f.read(), backend=default_backend())

    with open(input_file, 'rb') as f:
        data = f.read()

    # 生成对称密钥
    symmetric_key = os.urandom(32)

    # 使用RSA公钥加密对称密钥
    encrypted_symmetric_key = public_key.encrypt(
        symmetric_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )

    # 使用对称密钥加密文件内容
    iv = os.urandom(16)
    cipher = Cipher(algorithms.AES(symmetric_key), modes.CFB(iv), backend=default_backend())
    encryptor = cipher.encryptor()
    padded_data = sym_padding.PKCS7(128).padder().update(data) + sym_padding.PKCS7(128).padder().finalize()
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()

    # 将加密后的对称密钥、IV和文件内容写入输出文件
    with open(output_file, 'wb') as f:
        f.write(encrypted_symmetric_key)
        f.write(iv)
        f.write(encrypted_data)

# 解密文件
def decrypt_file(private_key_file, input_file, output_file):
    with open(private_key_file, 'rb') as f:
        private_key = serialization.load_pem_private_key(f.read(), password=None, backend=default_backend())

    with open(input_file, 'rb') as f:
        encrypted_symmetric_key = f.read(256)  # RSA加密后的对称密钥长度为256
        iv = f.read(16)
        encrypted_data = f.read()

    # 使用RSA私钥解密对称密钥
    symmetric_key = private_key.decrypt(
        encrypted_symmetric_key,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )

    # 使用对称密钥解密文件内容
    cipher = Cipher(algorithms.AES(symmetric_key), modes.CFB(iv), backend=default_backend())
    decryptor = cipher.decryptor()
    decrypted_data = decryptor.update(encrypted_data) + decryptor.finalize()
    unpadder = sym_padding.PKCS7(128).unpadder()
    decrypted_data = unpadder.update(decrypted_data) + unpadder.finalize()

    # 将解密后的文件内容写入输出文件
    with open(output_file, 'wb') as f:
        f.write(decrypted_data)

# 使用示例
encrypt_file('public_key.pem', 'plain.txt', 'encrypted.bin')
decrypt_file('private_key.pem', 'encrypted.bin', 'decrypted.txt')
