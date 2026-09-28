核心：**内核 printk //dev/kmsg 的特殊规则：尖括号 `<level>` 是内核日志优先级标记，会被内核特殊解析吃掉！**

[4888.187289] iot_sdk : <6>=== iot_sdk starting ===
[ 4888.187574] iot_sdk : <3>Usage: ./hello <directory_path>
[ 4891.664809] iot_sdk : <6>=== iot_sdk starting ===
[ 4891.665217] iot_sdk : <6>Input directory: /data/hj
[ 4891.665497] iot_sdk : <6>Config file path: /data/hj/etc/config.ini
[ 4891.665765] iot_sdk : <6>Successfully opened '/data/hj/etc/config.ini'
[ 4891.666026] iot_sdk : <6>iot_sdk running...
[ 4936.976411] iot_sdk : <6>iot_sdk still running (uptime: 82 minutes)
[ 4996.978569] iot_sdk : <6>iot_sdk still running (uptime: 83 minutes)
[ 5048.533359] === iot_sdk starting ===
[ 5048.534328] iot_sdk running...
console:/data/hj #
这里很奇怪，我的代码是 void log_message (int priority, const char *format, ...)
{
va_list args;
va_start (args, format);
// 输出到 logcat
vsyslog (priority, format, args);
// 输出到 dmesg（通过 /dev/kmsg）
FILE *kmsg = fopen ("/dev/kmsg", "w");
if (kmsg) {
char buffer [1024];
vsnprintf (buffer, sizeof (buffer), format, args);
//fprintf (kmsg, "iot_sdk : <% d>% s", priority, buffer);
fprintf (kmsg, "<% d>% s", priority, buffer);
fclose (kmsg);
}
// 同时输出到 stdout
vprintf (format, args);
va_end (args);
}
我一个是加了 iot_sdk 字符串，一个没有加。为何没有加的打印出来少了 < 6 > 相关的字符串

举例子：你往 `/dev/kmsg` 写入：
```
<6>hejian test msg
```
应该不会打印<6>。