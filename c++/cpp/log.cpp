#include "log.h"

static char sprintf_buf[1024]; 
static const char *log_level[4] ={"ERROR", "WARN", "INFO", "DEBUG"};


/*
 * @brief
 * @note
 * @param
 * @param
 * @return
 */
int dprintf_info(int level, const char *module, const char *pfun, const int line, const char *fmt, ...)
{
	va_list args;
	int n;
	va_start(args, fmt);
	n = vsnprintf(sprintf_buf, sizeof(sprintf_buf), fmt, args);
	printf("[%s][%s][%d]%s: %s", log_level[level], module, line, pfun, sprintf_buf);
	va_end(args);
	return n;
}
