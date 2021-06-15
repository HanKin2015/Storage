# -*- coding: utf-8 -*-
"""
@description:
    使用python执行shell脚本

@author: hankin
@date  : 2021.06.11
	
Copyright (c) 2021 HanKin. All rights reserved.
"""

import subprocess

cmd = r"./ls.sh"
cmd_result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
result = cmd_result.stdout.read()
print(result)

"""
#!/bin/bash

ls -l
"""


[root@ubuntu0006:/media/hankin/vdb/perl] #python python_shell.py
Traceback (most recent call last):
  File "python_shell.py", line 6, in <module>
    cmd_result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
  File "/usr/lib/python2.7/subprocess.py", line 711, in __init__
    errread, errwrite)
  File "/usr/lib/python2.7/subprocess.py", line 1343, in _execute_child
    raise child_exception
OSError: [Errno 2] No such file or directory
[root@ubuntu0006:/media/hankin/vdb/perl] #python3 python_shell.py
Traceback (most recent call last):
  File "python_shell.py", line 6, in <module>
    cmd_result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
  File "/usr/local/lib/python3.6/subprocess.py", line 709, in __init__
    restore_signals, start_new_session)
  File "/usr/local/lib/python3.6/subprocess.py", line 1344, in _execute_child
    raise child_exception_type(errno_num, err_msg, err_filename)
FileNotFoundError: [Errno 2] No such file or directory: './ls.sh': './ls.sh'
[root@ubuntu0006:/media/hankin/vdb/perl] #vim ls.shh
[root@ubuntu0006:/media/hankin/vdb/perl] #mv ls.shh ls.sh
[root@ubuntu0006:/media/hankin/vdb/perl] #python3 python_shell.py
Traceback (most recent call last):
  File "python_shell.py", line 6, in <module>
    cmd_result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
  File "/usr/local/lib/python3.6/subprocess.py", line 709, in __init__
    restore_signals, start_new_session)
  File "/usr/local/lib/python3.6/subprocess.py", line 1344, in _execute_child
    raise child_exception_type(errno_num, err_msg, err_filename)
PermissionError: [Errno 13] Permission denied: './ls.sh'
[root@ubuntu0006:/media/hankin/vdb/perl] #python python_shell.py
Traceback (most recent call last):
  File "python_shell.py", line 6, in <module>
    cmd_result = subprocess.Popen(cmd, stdout=subprocess.PIPE)
  File "/usr/lib/python2.7/subprocess.py", line 711, in __init__
    errread, errwrite)
  File "/usr/lib/python2.7/subprocess.py", line 1343, in _execute_child
    raise child_exception
OSError: [Errno 13] Permission denied
[root@ubuntu0006:/media/hankin/vdb/perl] #chmod +x ls.sh
[root@ubuntu0006:/media/hankin/vdb/perl] #python python_shell.py
总用量 132
-rwxr-xr-x 1 root root   547 6月   1 18:01 add_alias.sh
-rwxr-xr-x 1 root root 23816 6月  10 21:29 a.out
-rwxr-xr-x 1 root root 13168 6月   2 17:46 hello
-rwxr-xr-x 1 root root   124 6月   1 10:06 helloworld.pl
-rw-r--r-- 1 root root 21830 6月  10 21:28 hj.bmp
-rw-r--r-- 1 root root 22868 6月  10 21:20 icon.bmp
-rw-r--r-- 1 root root   160 6月   3 09:54 inline_study.c
-rw-r--r-- 1 root root   533 6月   3 09:45 inline_study.cpp
-rwxr-xr-x 1 root root    19 6月  11 09:46 ls.sh
-rw-r--r-- 1 root root   153 6月  11 09:41 python_shell.py
-rwxr-xr-x 1 root root  1217 6月   1 15:42 study.pl
-rw-r--r-- 1 root root  6384 6月  10 21:29 study_x11.cpp
-rw-r--r-- 1 root root  1428 6月  10 20:03 test.png
-rwxr-xr-x 1 root root   476 6月   1 11:12 yzy.pl

[root@ubuntu0006:/media/hankin/vdb/perl] #python3 python_shell.py
b'\xe6\x80\xbb\xe7\x94\xa8\xe9\x87\x8f 132\n-rwxr-xr-x 1 root root   547 6\xe6\x9c\x88   1 18:01 add_alias.sh\n-rwxr-xr-x 1 root root 23816 6\xe6\x9c\x88  10 21:29 a.out\n-rwxr-xr-x 1 r                oot root 13168 6\xe6\x9c\x88   2 17:46 hello\n-rwxr-xr-x 1 root root   124 6\xe6\x9c\x88   1 10:06 helloworld.pl\n-rw-r--r-- 1 root root 21830 6\xe6\x9c\x88  10 21:28 hj.bmp\n-rw-r--r--                 1 root root 22868 6\xe6\x9c\x88  10 21:20 icon.bmp\n-rw-r--r-- 1 root root   160 6\xe6\x9c\x88   3 09:54 inline_study.c\n-rw-r--r-- 1 root root   533 6\xe6\x9c\x88   3 09:45 inline_stu                dy.cpp\n-rwxr-xr-x 1 root root    19 6\xe6\x9c\x88  11 09:46 ls.sh\n-rw-r--r-- 1 root root   153 6\xe6\x9c\x88  11 09:41 python_shell.py\n-rwxr-xr-x 1 root root  1217 6\xe6\x9c\x88   1                 15:42 study.pl\n-rw-r--r-- 1 root root  6384 6\xe6\x9c\x88  10 21:29 study_x11.cpp\n-rw-r--r-- 1 root root  1428 6\xe6\x9c\x88  10 20:03 test.png\n-rwxr-xr-x 1 root root   476 6\xe6\x9c                \x88   1 11:12 yzy.pl\n'

