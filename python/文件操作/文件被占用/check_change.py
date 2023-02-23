# -*- coding: utf-8 -*-
"""
文 件 名: check_change.py
文件描述: Python实现的检测网站挂马程序
备    注: https://www.nhooo.com/note/qacshk.html
作    者: HanKin
创建日期: 2023.02.22
修改日期：2023.02.22

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import os
import sys
import subprocess

def update(path):
  f = open(file,'w')
  for root,dirs,files in os.walk(path):
    for name in files:
      line = os.path.join(root, name)
      (stdin,stderr) = subprocess.Popen(['md5sum',line],stdout=subprocess.PIPE).communicate()
      f.write(stdin)
  f.close()

def check(path):
  f = open(file,'r')
  for line in f:
    check_ok = """echo '%s' | md5sum -c > /dev/null 2>&1""" % line
    #print check_ok
    if not subprocess.call(check_ok, shell = True) == 0:
      abnormal = line.split()
      print abnormal[1]
  f.close()

def Usage():
  print '''
  Usage: python %s update /home/wwwroot
      python %s check /home/wwwroot
  ''' % (sys.argv[0],sys.argv[0])
  sys.exit()

if len(sys.argv) != 3:
  Usage()

file = 'file.key'
model = sys.argv[1]
path = sys.argv[2]

if os.path.exists(path) == False:
  print "\033[;31mThe directory or file does not exist\033[0m"
  sys.exit()
elif model == 'update':
  update(path)
elif model == 'check':
  check(path)
else:
  Usage()
  
def main():
    """主函数
    """

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))