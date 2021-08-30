#include "log.h"
#include <pthread.h>

static pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;

void init_log(const char *log_file_path)
{
    if (log_file_path == NULL) return;
    memset(LOG_FILE_PATH, 0, sizeof(LOG_FILE_PATH));
    strncpy(LOG_FILE_PATH, log_file_path, strlen(log_file_path));
    return;
}

static void printf_logv(int type, const char *format, va_list args)
{
    const char *type_names[] = { "[DEBUG]", "[INFO]", "[WARN]", "[ERROR]", "[FATAL]" };
    
    time_t timep = time(NULL);
	struct tm *lt = localtime(&timep);
	char ntime[MAX_LOGBUF_LEN] = {0};
	strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);

    char logmsg[MAX_LOGBUF_LEN];
    vsnprintf(logmsg, sizeof(logmsg), format, args);

    pthread_mutex_lock(&log_lock);
    FILE *fp = fopen(LOG_FILE_PATH, "a");
    if (!fp) {
        fprintf(stderr, "open log file<%s> failed, errno %s(%d)\n",
        LOG_FILE_PATH, strerror(errno), errno);
        return;
    }
    fprintf(fp, "%s %s [%" PRIu64 ":%" PRIu64 "] %s\n",
        ntime, type_names[type], (uint64_t)getpid(),
        (uint64_t)gettid(), logmsg);
    fclose(fp);
    pthread_mutex_unlock(&log_lock);
    return;
}

void printf_log(int type, const char *format, ...)
{
    va_list args;
    va_start (args, format);
    printf_logv(type, format, args);
    va_end (args);
    return;
}