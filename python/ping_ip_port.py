# -*- coding: utf-8 -*-
"""
Created on Tue Oct 13 11:19:23 2020

@author: hankin
"""

import os
import subprocess

subprocess.run("ping 127.0.0.1", shell=True)



for i in range(90, 100):
    ip = "172.22.192.{}".format(i)
    #ret = os.system('ping -n 2 -w 1 %s'%ip) #每个ip ping 2次，等待时间为1s
    cmd = "ping -n 1 -w 1 {}".format(ip)
    ret = subprocess.run(cmd, shell=True)
    print(subprocess.run("tree", shell=True).stdout)
    ret = subprocess.Popen(cmd, shell=True, stderr=subprocess.PIPE)
    print(ret.returncode)
    if ret:
        print('ping %s is fail'%ip)
    else:
        print('ping %s is ok'%ip)







