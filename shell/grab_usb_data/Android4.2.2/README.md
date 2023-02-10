## 1、脚本语法调整
之前的版本是在Android8.1上面调试执行，发现环境略有不同需要调整。
```
root@android:/sdcard # ./limit_file_size.sh
/system/bin/sh: ./limit_file_size.sh: can't execute: Permission denied
126|root@android:/sdcard # ll limit_file_size.sh
-rwxrwxr-x system   sdcard_rw     1206 2023-02-09 09:57 limit_file_size.sh
root@android:/sdcard # bash limit_file_size.sh
/system/bin/sh: bash: not found

# 只有sh命令
root@android:/mnt/sdcard # find / -name bash
root@android:/mnt/sdcard # find / -name sh
/system/bin/sh
find: /proc/97/task/166/fd/47: No such file or directory

# 语法错误
root@android:/mnt/sdcard # sh limit_file_size.sh
Bad mode
limit_file_size.sh[17]: /vendor/bin/grab_usb_data.sh: not found
du: /sdcard/usb_data_file.txt: No such file or directory
limit_file_size.sh[45]: [: 102400: unexpected operator/operand
du: /sdcard/usb_data_file.txt: No such file or directory
limit_file_size.sh[45]: [: 102400: unexpected operator/operand

root@android:/mnt/sdcard # which sh
/system/bin/sh
root@android:/mnt/sdcard # which bash
1|root@android:/mnt/sdcard # which busybox
/sbin/busybox

# sed命令在BusyBox里面
root@android:/sdcard # which sed
1|root@android:/sdcard # sed
BusyBox v1.11.1 (2009-03-11 09:17:49 CST) multi-call binary

Usage: sed [-efinr] pattern [files...]

Options:
        -e script       Add the script to the commands to be executed
        -f scriptfile   Add scriptfile contents to the
                        commands to be executed
        -i              Edit files in-place
        -n              Suppress automatic printing of pattern space
        -r              Use extended regular expression syntax

If no -e or -f is given, the first non-option argument is taken as the sed
script to interpret. All remaining arguments are names of input files; if no
input files are specified, then the standard input is read. Source files
will not be modified unless -i option is given.

1|root@android:/sdcard #
```

## 2、脚本后台执行无法查询进程id问题排查
后面想到脚本后台执行的时候一定会有一个进程id返回，可以通过这个值来杀死后台进程。
```
root@android:/sdcard # sh limit_file_size.sh &
[1] 9788
root@android:/sdcard # insmod: init_module '/system/lib/modules/usbmon.ko' failed (File exists)
002
2
006:

root@android:/sdcard # ps | grep sh
root      108   1     912    472   c043e4d4 4014809c S /system/bin/sh
shell     126   1     928    504   c06c3c50 401124a0 S /system/bin/sh
root      2725  2     0      0     c0527538 00000000 S flush-31:6
root      7068  2     0      0     c0527564 00000000 S flush-31:9
root      9097  1     888    460   c043e4d4 400e609c S /system/bin/sh
root      9114  9113  2792   1540  c0514634 4007a834 S ssh
root      9120  9104  928    536   c043e4d4 4013009c S /system/bin/sh
root      9788  9120  888    460   c043e4d4 4018709c S sh
root      9790  9788  888    460   c043e4d4 4017c09c S sh
root      9807  9790  892    92    bf0ab7c0 4017b4a0 S sh
root      9810  2     0      0     c0527538 00000000 S flush-31:8
```

ps命令的不完整导致无法追寻sh执行的详细命令：
```
root@android:/sdcard # help ps
/system/bin/sh: help: not found
127|root@android:/sdcard # ps -h
USER     PID   PPID  VSIZE  RSS     WCHAN    PC         NAME
root@android:/sdcard # ps --help
USER     PID   PPID  VSIZE  RSS     WCHAN    PC         NAME
root@android:/sdcard # info ps
/system/bin/sh: info: not found
127|root@android:/sdcard # man -k ps
man: invalid option -- k
BusyBox v1.11.1 (2009-03-11 09:17:49 CST) multi-call binary

Usage: man [OPTION]... [MANPAGE]...

Format and display manual page

Options:
        -a      Display all pages
        -w      Show page locations

1|root@android:/sdcard # man ps
man: /etc/man.conf: No such file or directory

也试过busybox，也试过a-z的所有参数不行。
```

在xubuntu上面发现只需要ps -u就可以查看详细命令，并且top -c命令也可以。

最终找到一种方法，使用lsof命令查找文件被占用的进程：
```
root@android:/sdcard # lsof | grep usb
usbipd      105       root  exe       ???                ???       ???        ??? /system/bin/usbipd
usbipd      105       root    0       ???                ???       ???        ??? /dev/null
usbipd      105       root    1       ???                ???       ???        ??? /dev/null
usbipd      105       root    2       ???                ???       ???        ??? /dev/null
usbipd      105       root    3       ???                ???       ???        ??? /dev/log/main
usbipd      105       root    4       ???                ???       ???        ??? /dev/initLog
usbipd      105       root    5       ???                ???       ???        ??? /dev/log/radio
usbipd      105       root    6       ???                ???       ???        ??? /dev/log/events
usbipd      105       root    7       ???                ???       ???        ??? /dev/ptmx
usbipd      105       root    8       ???                ???       ???        ??? /dev/ptmx
usbipd      105       root    9       ???                ???       ???        ??? /dev/ptmx
usbipd      105       root   10       ???                ???       ???        ??? /dev/log/system
usbipd      105       root   11       ???                ???       ???        ??? socket:[4136]
usbipd      105       root   13       ???                ???       ???        ??? /dev/__properties__ (deleted)
usbipd      105       root  mem       ???              1f:08         0        220 /system/bin/usbipd
usbipd      105       root  mem       ???              1f:08     20480        220 /system/bin/usbipd
sh         9807       root    3       ???                ???       ???        ??? /sys/kernel/debug/usb/usbmon/2u
grep       9808       root    1       ???                ???       ???        ??? /mnt/sdcard/usb_data_file.txt
```
然后发现9807这个进程id，然后通过ps来追寻父进程id，9790，9788。9120是/system/bin/sh就不用动了。

## 3、使用jobs命令
原来有个jobs -l命令可以查看后台执行的脚本，并伴有进程id。

注意使用kill -9杀死之后，子进程还是依然会存在，并交由1进程管理：
```
root@android:/sdcard # ps | grep sh
root      108   1     912    472   c043e4d4 4014809c S /system/bin/sh
shell     126   1     928    504   c06c3c50 401124a0 S /system/bin/sh
root      2725  2     0      0     c0527538 00000000 S flush-31:6
root      7068  2     0      0     c0527564 00000000 S flush-31:9
root      9097  1     888    460   c043e4d4 400e609c S /system/bin/sh
root      9114  9113  2792   1540  c0514634 4007a834 S ssh
root      9120  9104  928    536   c043e4d4 4013009c S /system/bin/sh
root      10495 9120  892    464   c043e4d4 400ff09c S sh
root      10497 10495 888    460   c043e4d4 400bc09c S sh
root      10514 10497 892    92    bf0ab7c0 400bb4a0 S sh

root@android:/sdcard # kill -9 10495
root@android:/sdcard # ps | grep sh
root      108   1     912    472   c043e4d4 4014809c S /system/bin/sh
shell     126   1     928    504   c06c3c50 401124a0 S /system/bin/sh
root      2725  2     0      0     c0527538 00000000 S flush-31:6
root      7068  2     0      0     c0527564 00000000 S flush-31:9
root      9097  1     888    460   c043e4d4 400e609c S /system/bin/sh
root      9114  9113  2792   1540  c0514634 4007a834 S ssh
root      9120  9104  928    536   c043e4d4 4013009c S /system/bin/sh
root      10347 1     892    92    bf0ab7c0 401de4a0 S sh
root      10497 1     888    460   c043e4d4 400bc09c S sh
root      10514 10497 892    92    bf0ab7c0 400bb4a0 S sh
```
似乎只能一个一个去杀死，搜索了一遍只有killall命令，但是在这里不适用。