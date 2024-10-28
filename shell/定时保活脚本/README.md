# 1、需求
使用shell脚本监控一个nohub python t.py &执行的后台进程，统计它占用的VIRT以及句柄数量，如果VIRT超过了5g或者句柄数量超过了600就杀死重新拉起。并把脚本放在每日定时执行中。

# 2、实现
D:\Github\Storage\shell\定时保活脚本\py_daemon.sh
```
[root@ubuntu0006:~/cmake] #bash py_daemon.sh
/root/cmake/k.py file start pid is 25257
VIRT:  27840 KB, Handles: 3
Conditions met. Restarting process...
nohup: 把输出追加到'nohup.out'
/root/cmake/k.py file restart pid is 26144
```

# 3、设置定时任务
要将此脚本设置为每日定时执行，可以使用cron。假设你将脚本保存为/path/to/monitor_script.sh，并确保它是可执行的：
```
chmod +x /path/to/py_daemon.sh
```

然后，编辑crontab来添加定时任务：
```
crontab -e
```
在crontab中添加以下行以每天执行一次（例如，每天凌晨2点）：
```
0 2 * * * /path/to/monitor_script.sh >> /path/to/monitor_log.txt 2>&1
```
这将会在每天凌晨2点执行脚本，并将输出记录到/path/to/monitor_log.txt中。

```
* * * * * command_to_execute
- - - - -
| | | | |
| | | | +---- 星期几 (0 - 7) (星期天为0或7)
| | | +------ 月份 (1 - 12)
| | +-------- 日期 (1 - 31)
| +---------- 小时 (0 - 23)
+------------ 分钟 (0 - 59)
```
分钟：任务在每小时的第几分钟执行。
小时：任务在每天的第几个小时执行。
日期：任务在每月的第几天执行。
月份：任务在每年的第几个月执行。
星期几：任务在每周的第几天执行。
*：表示任何值。例如，*在分钟位置表示每分钟都执行。
,：用于分隔多个值。例如，1,15在分钟位置表示在第1和第15分钟执行。
-：用于指定范围。例如，1-5在小时位置表示从1点到5点之间每小时执行。
/：用于指定步长。例如，*/5在分钟位置表示每5分钟执行一次。

# 4、测试
因为脚本的日志即通过打印到文件也打印到输出窗口，因此这里也可以把日志输出到文件。

每分钟执行一次脚本。
```
*/1 * * * * /root/cmake/py_daemon.sh >> /tmp/monitor_log.txt 2>&1
```