参考：https://blog.csdn.net/qq_28657577/article/details/80738161

根本行不通。

```
[root@ubuntu0006:/media/hankin/vdb/TransferStation] #/etc/init.d/hello.sh start
start hello
hello world
^C
[root@ubuntu0006:/media/hankin/vdb/TransferStation] #systemctl start hello.sh
Failed to start hello.sh.service: Unit hello.sh.service not found.
[root@ubuntu0006:/media/hankin/vdb/TransferStation] #service hello.sh start
Failed to start hello.service: Unit hello.service not found.
```