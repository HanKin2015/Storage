#coding=gbk
'''
windows中copy命令详解
功能：将一份文件或者多份文件复制到另一个位置

用法：

copy [/D] [/V] [/N] [/Y|/-Y] [/Z] [/A | /B] source [/A | /B] [+ source [/A | /B] [+...]] [destination [/A | /B]]
source            指定要复制的文件。 
/A                 表示一个 ASCII 文本文件。 
/B                 表示一个二进位文件。 
/D                 允许解密要创建的目标文件 
destination    为新文件指定目录和/或文件名。
/V                 验证新文件写入是否正确。
/N                 复制带有非 8dot3 名称的文件时， 尽可能使用短文件名。 
/Y                 不使用确认是否要改写现有目标文件 的提示。 
/-Y                使用确认是否要改写现有目标文件 的提示。 
/Z                 用可重新启动模式复制已联网的文件。 

注意：多个文件用通配符或者file1+file2+file3格式 

例如：将1.png 和 1.php 复制到2.png 


1 copy 1.png/b+1.php/a 2.png
意义：将秘密藏在别人的肚纸

U盘拷贝到电脑中，同一个文件是秒传
- 尝试清空回收站
- 重命名文件
- 重命名文件类型
- 电脑新建文件夹等等
发现增加/V参数后大概多了10分之一的时间，也还是存在读缓存。

没结论：https://bbs.csdn.net/topics/392184082?list=189553
可能还真与这个高速写入缓存有关，但是无法关闭，这真是个问题。
windows无法更改此设备的写入高速缓存设置
说的很详细，但还是不行：https://bbs.luobotou.org/thread-46508-1-1.html

两个字：放弃
'''

import os
import time
import datetime
import sys

disk = sys.argv[1]

i = 1
with open('log.log', 'a+') as f:
    f.write("{}-----{}---\n".format(i,datetime.datetime.now()))

the_file_name = "1.txt"
while True:
    print(i)
    file_name_new = "1.txt{}".format(int(time.time()))
    os.system("rename {} {}".format(the_file_name, file_name_new))
    the_file_name = file_name_new
    print(datetime.datetime.now())
    os.system("copy /Y /V {} {}:\\".format(the_file_name, disk))
    print(1, datetime.datetime.now())
    os.system("del {}".format(the_file_name))
    time.sleep(5)
    print(2, datetime.datetime.now())
    res = os.system("copy /Y /V {}:\\{} .\\".format(disk, the_file_name))
    print(3, datetime.datetime.now())
    os.system("del {}:\\{}".format(disk, the_file_name))
    if res != 0:
        with open('log.log', 'a+') as f:
            f.write("{}-----{}---:{}\n".format(i,datetime.datetime.now(), res))
    i = i + 1