#ifndef LOG_H
#define LOG_H

#define FORMAT "%s %s [%s: %d: %s]"

#define LOG_INFO(fmt, ...) \
        printf(FORMAT fmt "\n", __DATE__, __TIME__, __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__);
#define LOG_WARN(fmt, ...) \
        printf(FORMAT "\n", __DATE__, __TIME__, __FILE__, __LINE__, __FUNCTION__);








#endif
