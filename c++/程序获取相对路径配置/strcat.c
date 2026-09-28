#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <syslog.h>
#include <errno.h>
#include <sys/stat.h>

// 打印到内核日志和标准输出的辅助函数
// 在 Android 中，syslog () 函数默认输出到 /dev/log/main（即 logcat），而不是内核的 dmesg。
void log_message (int priority, const char *format, ...)
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
        fprintf (kmsg, "iot_sdk : <% d>% s", priority, buffer);
        fclose (kmsg);
    }
    // 同时输出到 stdout
    vprintf (format, args);
    va_end (args);
}

int main (int argc, char *argv [])
{
    // 打开系统日志
    openlog ("iot_sdk", LOG_PID | LOG_CONS | LOG_NOWAIT, LOG_DAEMON);
    log_message (LOG_INFO, "=== iot_sdk starting ===\n");
    // 检查参数
    if (argc < 2) {
        log_message (LOG_ERR, "Usage: % s <directory_path>\n", argv [0]);
        return 1;
    }
    // 获取并规范化输入目录
    char input_dir [PATH_MAX];
    if (realpath (argv [1], input_dir) == NULL) {
        // 如果 realpath 失败，使用原始输入
        strncpy (input_dir, argv [1], sizeof (input_dir) - 1);
        input_dir [sizeof (input_dir) - 1] = '\0';
        log_message (LOG_WARNING, "Cannot resolve path '% s', using as-is\n", argv [1]);
    }
    log_message (LOG_INFO, "Input directory: % s\n", input_dir);
    // 确保目录存在
    struct stat st;
    if (stat (input_dir, &st) != 0 || !S_ISDIR (st.st_mode)) {
        log_message (LOG_ERR, "Directory '% s' does not exist or is not a directory\n", input_dir);
        return 1;
    }
    // 拼接配置文件路径
    char config_path [PATH_MAX];
    int len = snprintf (config_path, sizeof (config_path), "% s/etc/config.ini", input_dir);
    if (len >= sizeof (config_path)) {
        log_message (LOG_ERR, "Config path too long\n");
        return 1;
    }
    log_message (LOG_INFO, "Config file path: % s\n", config_path);
    // 检查配置文件是否存在
    if (access (config_path, F_OK) != 0) {
        log_message (LOG_ERR, "Config file '% s' does not exist (errno=% d)\n",
        config_path, errno);
        return 1;
    }
    // 打开配置文件
    FILE *fp = fopen (config_path, "r");
    if (!fp) {
        log_message (LOG_ERR, "Failed to open '% s': % s\n",
        config_path, strerror (errno));
        return 1;
    }
    log_message (LOG_INFO, "Successfully opened '% s'\n", config_path);
    // 读取并显示文件内容（可选）
    char buffer [256];
    while (fgets (buffer, sizeof (buffer), fp)) {
        // 去掉换行符
        buffer [strcspn (buffer, "\n")] = '\0';
        log_message (LOG_DEBUG, "Config content: % s\n", buffer);
    }
    fclose (fp);
    // 保持程序运行
    log_message (LOG_INFO, "iot_sdk running...\n");
    int count = 0;
    while (1) {
        sleep (10);
        count++;
        if (count % 6 == 0) {  // 每分钟打印一次
            log_message (LOG_INFO, "iot_sdk still running (uptime: % d minutes)\n",
            count / 6);
        }
    }
    log_message (LOG_INFO, "=== iot_sdk exiting ===\n");
    closelog ();
    return 0;
}