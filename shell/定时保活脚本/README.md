设置定时任务
要将此脚本设置为每日定时执行，可以使用cron。假设你将脚本保存为/path/to/monitor_script.sh，并确保它是可执行的：

bash
chmod +x /path/to/monitor_script.sh
然后，编辑crontab来添加定时任务：

bash
crontab -e
在crontab中添加以下行以每天执行一次（例如，每天凌晨2点）：

bash
0 2 * * * /path/to/monitor_script.sh >> /path/to/monitor_log.txt 2>&1
这将会在每天凌晨2点执行脚本，并将输出记录到/path/to/monitor_log.txt中。

```
[root@ubuntu0006:~/cmake] #bash py_daemon.sh
/root/cmake/k.py file start pid is 25257
VIRT:  27840 KB, Handles: 3
Conditions met. Restarting process...
nohup: 把输出追加到'nohup.out'
/root/cmake/k.py file restart pid is 26144
```