from unrar import rarfile
import os
from itertools import chain
import itertools as its
import time
from tqdm import tqdm

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
    out_put_file_path = '{}'.format(file.namelist()[0])
 
    try:
        file.extractall(path=output_path, pwd=pwd)
        # 如果发现文件被解压处理，移除该文件
        os.remove(out_put_file_path)
        # 说明当前密码有效，并告知
        print('Find password is "{}"'.format(pwd))
        return True
    except Exception as ex:
        # 密码不正确
        #print(ex)
        #print('"{}" is not correct password!'.format(pwd))
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
    print('t')
    while min_digits <= max_digits:
        pwds = its.product(words, repeat=min_digits)
        for pwd in pwds:
            yield ''.join(pwd)
        min_digits += 1
    print('me')


file_path = './test.rar'
output_path = './'

# 密码范围
# words = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'  # 涉及到生成密码的参数
words = '0123456789abcdefghij'
pwds = get_password(2, 2, words)
print(type(pwds))

# 开始查找密码
start = time.time()
print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

# 密码总数
pwds_sum = len(set(words))^2

print(pwds_sum)

for i in tqdm(range(10), total=10, ncols=5, mininterval=0.1):
    time.sleep(0.5)

#tqdm(range(10), total=10)
for pwd in tqdm(chain.from_iterable(pwds), total=pwds_sum):
    if get_pwd(file_path, output_path, pwd=pwd):
        break

end = time.time()
print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
spend_time   = end - start
spend_hour   = spend_time // 3600
spend_minute = (spend_time - spend_hour * 3600) // 60
spend_second = spend_time - spend_hour * 3600 - spend_minute * 60
print('程序耗时: %d小时%d分%d秒.' % (spend_hour, spend_minute, spend_second))
