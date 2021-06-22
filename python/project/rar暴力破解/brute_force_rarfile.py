import time
from typing import List
from tqdm import tqdm
from itertools import chain
from zipfile import ZipFile
from unrar import rarfile
import threading

# 1、开始时间
start = time.time()
print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

# 2、chr(97) -> 'a' 这个变量保存了密码包含的字符集
dictionaries = [chr(i) for i in
                chain(range(102, 107),    # a97 - z123
                      #range(65, 91),    # A - Z
                      #range(56, 57),
                      range(53, 57))]    # 0 48- 9 58
#dictionaries.extend(['.com', 'www.'])    # 添加自定义的密码字符集
print(dictionaries)
#time.sleep(1000)

# 3、rar文件路径
file_path = './test.rar'

# 4、密码生成器
def all_passwd(dictionaries: List[str], maxlen: int):
    # 返回由 dictionaries 中字符组成的所有长度为 maxlen 的字符串

    def helper(temp: list, start: int, n: int):
        # 辅助函数，是个生成器
        if start == n:    # 达到递归出口
            yield ''.join(temp)
            return
        for t in dictionaries:
            temp[start] = t    # 在每个位置
            yield from helper(temp, start + 1, n)

    yield from helper([0] * maxlen, 0, maxlen)

rfile = rarfile.RarFile(file_path) # 很像open

def extract(rfile: rarfile.RarFile, pwd: str) -> bool:
    # rfile: 一个rarfile.RarFile类, pwd: 密码
    
    try:
        # 获取锁，用于线程同步
        #threadLock.acquire()
        rfile.extractall(path='./', pwd=pwd)    # 密码输入错误的时候会报错
        # 释放锁，开启下一个线程
        #threadLock.release()
        now = time.time()                                      # 故使用 try - except 语句
        print(f"Password is: {pwd}")                           # 将正确的密码输出到控制台
        print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
        return True
    except Exception as ex:
        # 释放锁，开启下一个线程
        #threadLock.release()
        if pwd == 'hj58':
            print(f"{ex}-------Password is not: {pwd}")
        return False    
# 用 bool 类型的返回值告诉主程序是否破解成功 (意思就是返回 True 了以后就停止)

lengths = [4]    # 密码长度
total = sum(len(dictionaries) ** k for k in lengths)    # 密码总数
threadLock = threading.Lock()

#print(list(all_passwd(dictionaries, 2)))
#print(len(list(all_passwd(dictionaries, 2)))) 

threads = []
for pwd in tqdm(chain.from_iterable(all_passwd(dictionaries, maxlen) for maxlen in lengths), total=total, ncols=10):
    '''使用多线程可提高速度'''
#    t = threading.Thread(target=extract, args=(rfile, pwd))
#    t.start()
#    threads.append(t)
    if extract(rfile, pwd):    # 记得extract函数返回的是bool类型的哦
        break
    
# 等待所有线程完成
#for t in threads:
#    t.join()
print ("退出主线程")
end = time.time()
print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))
spend_time   = end - start
spend_hour   = spend_time // 3600
spend_minute = (spend_time - spend_hour * 3600) // 60
spend_second = spend_time - spend_hour * 3600 - spend_minute * 60
print('程序耗时: %d小时%d分%d秒.' % (spend_hour, spend_minute, spend_second))
