```
[root@ubuntu0006:~/cmake] #bash log.sh
2024-10-21 10:09:34 - 这是另一条日志信息。
abc
 [ 2024-10-21 10:09:34 ] - [ INFO ] -  log.sh - echo abc - 0
log.sh: 行 32: abcd: 未找到命令
 [ 2024-10-21 10:09:34 ] - [ ERROR ] - log.sh - abcd - 127
root     tty7         2024-09-14 16:21 (:0)
root     pts/7        2024-09-14 16:21 (:0)
root     pts/8        2024-09-14 16:21 (:0)
root     pts/2        2024-10-17 21:04 (172.22.64.246)
 [ 2024-10-21 10:09:34 ] - [ INFO ] -  log.sh - test - 0
[root@ubuntu0006:~/cmake] #abc
-bash: abc: 未找到命令
[root@ubuntu0006:~/cmake] #cat /tmp/logfile-20241021
 [ 2024-10-21 10:09:34 ] - [ INFO ] -  log.sh - echo abc - 0
 [ 2024-10-21 10:09:34 ] - [ ERROR ] - log.sh - abcd - 127
 [ 2024-10-21 10:09:34 ] - [ INFO ] -  log.sh - test - 0
```