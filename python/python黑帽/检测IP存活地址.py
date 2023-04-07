# -*- coding: utf-8 -*-
import _thread
import time
from subprocess import Popen, PIPE
import sys

def ping_check(ip):
    check = Popen("ping {0} \n".format(ip), stdin=PIPE, stdout=PIPE, shell=True)
    data = check.stdout.read()  #数据
    data = data.decode("gbk")   #编码转换:byte->str
    if 'TTL' in data: #存活
        sys.stdout.write('%s is UP \n' % ip)

#主函数
if __name__ == '__main__':
    #寻找目标 ichunqiu  1.31.128.240
    for i in range(1, 255):
        ip = '110.242.68.' + str(i)
        #多线程方法
        _thread.start_new_thread(ping_check, (ip, ))
        time.sleep(0.1)
