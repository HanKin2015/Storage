```
exec [ <seclabel> [ <user> [ <group> ]* ] ] -- <command> [ <argument> ]*

exec - system system -- /system/bin/sh -c "/data/hj/print_log.sh exec"
```
- \<seclabel>：SELinux 安全上下文。
- \<user>/<group>：以哪个用户/组身份运行。
- --：分隔符。表示 init 参数的结束和要执行的命令的开始。
- \<command>：要执行的可执行文件路径。
- \<argument>：传递给该命令的参数。

- exec：init 关键字。
- -：<seclabel>，保持当前 SELinux 上下文。
- /system/bin/sh：要执行的命令。因为 -- 被省略了，init 会自动推断。
- -c：传递给 shell 的第一个参数。
- "/data/hj/print_log.sh startexec"：传递给 shell 的第二个参数。

因此在rc文件打印日志可以通过此命令：
```
exec -- /system/bin/sh -c "/data/hj/print_log.sh start_log"
```

## 挂载debug文件夹
```
mount -t debugfs none /sys/kernel/debug
```