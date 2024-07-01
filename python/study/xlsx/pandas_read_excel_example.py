# -*- coding: utf-8 -*-
"""
文 件 名: pandas_read_excel_example.py
文件描述: 使用pandas打开xlsx表格
作    者: HanKin
创建日期: 2023.09.05
修改日期：2024.07.01

Copyright (c) 2024 HanKin. All rights reserved.
"""

import time
import pandas as pd

ORIGIN_XLSX_FILE_PATH = r"C:\Users\User\Downloads\兼容数据黑白名单导出表格_2024-07-01.xlsx"
XLSX_FILE_PATH = r"D:\compatibility_list.xlsx"

def match_vid_pid():
    """匹配usb设备（在xlsx文件中是否存在）
    """
    
    scanning_gun = '0525:A4A7'
    df = pd.read_excel(XLSX_FILE_PATH, sheet_name='Sheet1')
    found_count = 0
    for index, vid_pid in enumerate(df['vid_pid']):
        vid_pids = vid_pid.split(';')
        is_found = False
        for elem in vid_pids:
            if scanning_gun.lower() == elem.lower():
                is_found = True
                break
        if is_found:
            print('usb device [{}] is found in index {}[{}]'.format(scanning_gun, index+2, vid_pid))
            print('{}'.format(df.iloc[index]['remark']))
            found_count += 1
    if found_count == 0:
        print('usb device [{}] is not found'.format(scanning_gun))

def check_vid_pid_valid():
    """检查vid_pid列合法性（是否以分号隔开）
    """
    # 读取 Excel 文件
    df = pd.read_excel(XLSX_FILE_PATH, sheet_name='Sheet1')

    # 打印数据框的前几行
    #print(df.head())
    
    # 打印工作表大小
    print(df.shape)
    
    # 遍历vid_pid列
    invalid_count = 0
    for index, vid_pid in enumerate(df['vid_pid']):
        vid_pids = vid_pid.split(';')
        is_valid = True
        for elem in vid_pids:
            if len(elem) != 9:
                is_valid = False
                break
        if not is_valid:
            print('index {} is invalid[{}]'.format(index+2, vid_pid))
            invalid_count += 1
    print('invalid_count = {}'.format(invalid_count))

def duplicate_data():
    """找出重复的数据
    """
    df = pd.read_excel(XLSX_FILE_PATH, sheet_name='Sheet1')
    zip_list = list(zip(df['model'], df['vendor'], df['vid_pid']))
    duplicate = []
    for item in zip_list:
        if zip_list.count(item) > 1 and item not in duplicate:
            duplicate.append(item)
    print('there are {} duplicates'.format(duplicate))

def pretreatment():
    """对xlsx文件进行预处理（筛选出需要的数据）
    """
    df = pd.read_excel(ORIGIN_XLSX_FILE_PATH, sheet_name='VDI_peripheral')
    df = df['', '', '']
    df.to_excel(XLSX_FILE_PATH)

def encrypt_file(input_file, output_file):
    """
    使用AES算法加密文件
    :param input_file: 输入文件
    :param output_file: 输出文件
    :return null: 无
    """
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

def main():
    """主函数
    """
    
    check_vid_pid_valid()
    duplicate_data()
    match_vid_pid()
    
    x = [1, 2, 3, 4]
    y = [11, 22, 33, 44]
    z = zip(x, y)
    print(z)
    for item in z:
        print(item)
    print(type(z))

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()
    
    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
