from unrar import rarfile
import os

import itertools as its
import time

from concurrent.futures import ThreadPoolExecutor


def get_pwd(file_path, output_path, pwd):
    '''
    判断密码是否正确
    :param file_path: 需要破解的文件路径，这里仅对单个文件进行破解
    :param output_path: 解压输出文件路径
    :param pwd: 传入的密码
    :return:
    '''
    # 传入被解压的文件路径，生成待解压文件对象
    file = rarfile.RarFile(file_path)
    # 输出解压后的文件路径
    out_put_file_path = 'rar/{}'.format(file.namelist()[0])
    print(file_path, output_path, pwd)
    file.extractall(path=output_path, pwd=pwd)
    try:
        # 如果发现文件被解压处理，移除该文件
        os.remove(out_put_file_path)
        # 说明当前密码有效，并告知
        print('Find password is "{}"'.format(pwd))
        return True
    except Exception as e:
        # 密码不正确
        print('"{}" is nor correct password!'.format(pwd))
        # print(e)
        return False


def get_password(min_digits, max_digits, words):
    """
    密码生成器
    :param min_digits: 密码最小长度
    :param max_digits: 密码最大长度
    :param words: 密码可能涉及的字符
    :return: 密码生成器
    """
    while min_digits <= max_digits:
        pwds = its.product(words, repeat=min_digits)
        for pwd in pwds:
            yield ''.join(pwd)
        min_digits += 1


file_path = './test.rar'
output_path = './'

# 密码范围
# words = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'  # 涉及到生成密码的参数
words = '0123456789abcdefghij'
pwds = get_password(1, 4, words)
# 开始查找密码
start = time.time()
pwd='hj5'
if get_pwd(file_path, output_path, pwd=pwd):
    print(pwd)
else:
    print(pwd, pwd)
"""
while True:
    pwd = next(pwds)
    if get_pwd(file_path, output_path, pwd=pwd):
        break
"""
end = time.time()
print('程序耗时{}'.format(end - start))
