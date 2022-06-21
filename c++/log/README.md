
# 示例
2022-05-05 16:50:34 [3089:3089] [info] [keyboard]study.c: 123 {main:36}
2022-05-06 16:12:54 [3089:3089] [debug] [keyboard]study.c: this is a error! {main:37}
2022-05-06 20:56:23 [3089:3089] [warning] [keyboard]study.c: warn: this is a error, err: 55. {main:38}

# 定标准
年-月-日 时:分:秒 [进程:线程] [日志级别] [模块名]文件名: 日志内容 {函数名:行数}

# 临时调试专用
```
#define LOG(format, ...) printf_log(format, ## __VA_ARGS__)
void printf_log(int type, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char logmsg[4096];
    vsnprintf(logmsg, sizeof(logmsg), format, args);

    FILE *fp = fopen("/home/debug.log", "a");
    if (!fp) {
        fprintf(stderr, "open log file</home/debug.log> failed, errno %s(%d)\n",
        strerror(errno), errno);
        return;
    }
    fprintf(fp, "%s\n", logmsg);
    fclose(fp);
    fp = NULL;

    va_end (args);
    return;
}
```











