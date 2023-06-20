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

# 该项目日志文件调用使用方式
该版本还是有一些年份了，2021.08.23版本，现在已是2023.06.19，这次不改变整体逻辑，做一点小优化，可不需要初始化日志文件位置。
示例见：D:\Github\Storage\c++\log\test_log.cpp
```
[root@ubuntu0006:~/cmake] #g++ test_log.cpp log.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
not init log file path, use default log file path, ./log/project.log.
2023-06-19 15:25:06 [INFO] [17927:17927] [test_log.cpp:6:main] I am hero, 34
2023-06-19 15:25:06 [ERROR] [17927:17927] [test_log.cpp:9:main] I am hero, 34
```








